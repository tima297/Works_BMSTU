CREATE TABLE IF NOT EXISTS employees (
    id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    position VARCHAR(100),
    salary DECIMAL(10, 2) CHECK (salary >= 0)
);

-- Создание таблицы проектов
CREATE TABLE IF NOT EXISTS projects (
    id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    budget DECIMAL(15, 2) CHECK (budget >= 0)
);

-- Создание таблицы назначений сотрудников на проекты
CREATE TABLE IF NOT EXISTS employee_projects (
    employee_id INT,
    project_id INT,
    role_in_project VARCHAR(100),
    PRIMARY KEY (employee_id, project_id),
    FOREIGN KEY (employee_id) REFERENCES employees(id) ON DELETE CASCADE,
    FOREIGN KEY (project_id) REFERENCES projects(id) ON DELETE CASCADE
);

-- Создание таблицы аудита
CREATE TABLE IF NOT EXISTS audit_log (
    id SERIAL PRIMARY KEY,
    username VARCHAR(100),
    action_type VARCHAR(50),
    table_name VARCHAR(100),
    record_id INT,
    old_value TEXT,
    new_value TEXT,
    action_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    description TEXT
);

-- =============================================
-- 2. СОЗДАНИЕ РОЛЕЙ И ПОЛЬЗОВАТЕЛЕЙ
-- =============================================

-- Создание роли администратора
CREATE ROLE admin_role;
GRANT ALL PRIVILEGES ON DATABASE postgres TO admin_role;
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO admin_role;
GRANT ALL PRIVILEGES ON ALL SEQUENCES IN SCHEMA public TO admin_role;

-- Создание роли менеджера
CREATE ROLE manager_role;
GRANT SELECT ON employees, projects TO manager_role;
GRANT INSERT, SELECT, DELETE ON employee_projects TO manager_role;
GRANT USAGE ON SCHEMA public TO manager_role;

-- Создание роли аналитика
CREATE ROLE analyst_role;
GRANT SELECT ON projects, employee_projects TO analyst_role;
GRANT USAGE ON SCHEMA public TO analyst_role;

-- Создание пользователей для каждой роли
CREATE USER admin_user WITH PASSWORD 'admin123';
CREATE USER manager_user WITH PASSWORD 'manager123';
CREATE USER analyst_user WITH PASSWORD 'analyst123';

-- Назначение ролей пользователям
GRANT admin_role TO admin_user;
GRANT manager_role TO manager_user;
GRANT analyst_role TO analyst_user;

-- =============================================
-- 3. ФУНКЦИИ ДЛЯ ТРАНЗАКЦИЙ И ПРОВЕРОК
-- =============================================

-- Функция для логирования действий
CREATE OR REPLACE FUNCTION log_audit(
    p_action_type VARCHAR(50),
    p_table_name VARCHAR(100),
    p_record_id INT,
    p_old_value TEXT DEFAULT NULL,
    p_new_value TEXT DEFAULT NULL,
    p_description TEXT DEFAULT NULL
)
RETURNS VOID AS $$
BEGIN
    INSERT INTO audit_log (username, action_type, table_name, record_id, 
                          old_value, new_value, description)
    VALUES (current_user, p_action_type, p_table_name, p_record_id,
            p_old_value, p_new_value, p_description);
END;
$$ LANGUAGE plpgsql;

-- Функция для обновления бюджета проекта с транзакцией
CREATE OR REPLACE FUNCTION update_project_budget(
    p_project_id INT,
    p_new_budget DECIMAL(15, 2)
)
RETURNS TEXT AS $$
DECLARE
    v_old_budget DECIMAL(15, 2);
BEGIN
    -- Проверка существования проекта
    IF NOT EXISTS (SELECT 1 FROM projects WHERE id = p_project_id) THEN
        RAISE EXCEPTION 'Проект с ID % не найден', p_project_id;
    END IF;
    
    -- Проверка корректности бюджета
    IF p_new_budget < 0 THEN
        RAISE EXCEPTION 'Бюджет не может быть отрицательным';
    END IF;
    
    -- Получаем старое значение
    SELECT budget INTO v_old_budget FROM projects WHERE id = p_project_id;
    
    -- Обновляем бюджет
    UPDATE projects SET budget = p_new_budget WHERE id = p_project_id;
    
    -- Логируем действие
    PERFORM log_audit('UPDATE', 'projects', p_project_id, 
                     v_old_budget::TEXT, p_new_budget::TEXT,
                     'Обновление бюджета проекта');
    
    RETURN 'Бюджет проекта успешно обновлен';
EXCEPTION
    WHEN OTHERS THEN
        RAISE EXCEPTION 'Ошибка при обновлении бюджета: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- Функция для добавления сотрудника в проект
CREATE OR REPLACE FUNCTION add_employee_to_project(
    p_employee_id INT,
    p_project_id INT,
    p_role VARCHAR(100)
)
RETURNS TEXT AS $$
DECLARE
    v_employee_name VARCHAR(100);
    v_project_name VARCHAR(100);
BEGIN
    -- Проверка существования сотрудника
    IF NOT EXISTS (SELECT 1 FROM employees WHERE id = p_employee_id) THEN
        RAISE EXCEPTION 'Сотрудник с ID % не найден', p_employee_id;
    END IF;
    
    -- Проверка существования проекта
    IF NOT EXISTS (SELECT 1 FROM projects WHERE id = p_project_id) THEN
        RAISE EXCEPTION 'Проект с ID % не найден', p_project_id;
    END IF;
    
    -- Проверка на дублирование назначения
    IF EXISTS (SELECT 1 FROM employee_projects 
               WHERE employee_id = p_employee_id AND project_id = p_project_id) THEN
        RAISE EXCEPTION 'Сотрудник уже назначен на этот проект';
    END IF;
    
    -- Получаем имена для лога
    SELECT name INTO v_employee_name FROM employees WHERE id = p_employee_id;
    SELECT name INTO v_project_name FROM projects WHERE id = p_project_id;
    
    -- Добавляем назначение
    INSERT INTO employee_projects (employee_id, project_id, role_in_project)
    VALUES (p_employee_id, p_project_id, p_role);
    
    -- Логируем действие
    PERFORM log_audit('INSERT', 'employee_projects', p_employee_id,
                     NULL, p_role || ' на проект ' || p_project_id,
                     'Назначение сотрудника ' || v_employee_name || 
                     ' на проект ' || v_project_name);
    
    RETURN 'Сотрудник успешно назначен на проект';
EXCEPTION
    WHEN OTHERS THEN
        RAISE EXCEPTION 'Ошибка при назначении сотрудника: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- Функция для удаления сотрудника из проекта
CREATE OR REPLACE FUNCTION remove_employee_from_project(
    p_employee_id INT,
    p_project_id INT
)
RETURNS TEXT AS $$
DECLARE
    v_role VARCHAR(100);
    v_employee_name VARCHAR(100);
    v_project_name VARCHAR(100);
BEGIN
    -- Получаем информацию для лога
    SELECT e.name, p.name, ep.role_in_project 
    INTO v_employee_name, v_project_name, v_role
    FROM employees e
    JOIN projects p ON p.id = p_project_id
    JOIN employee_projects ep ON ep.employee_id = p_employee_id 
                              AND ep.project_id = p_project_id
    WHERE e.id = p_employee_id;
    
    IF v_employee_name IS NULL THEN
        RAISE EXCEPTION 'Назначение не найдено';
    END IF;
    
    -- Удаляем назначение
    DELETE FROM employee_projects 
    WHERE employee_id = p_employee_id AND project_id = p_project_id;
    
    -- Логируем действие
    PERFORM log_audit('DELETE', 'employee_projects', p_employee_id,
                     v_role || ' на проект ' || p_project_id, NULL,
                     'Удаление сотрудника ' || v_employee_name || 
                     ' из проекта ' || v_project_name);
    
    RETURN 'Сотрудник успешно удален из проекта';
EXCEPTION
    WHEN OTHERS THEN
        RAISE EXCEPTION 'Ошибка при удалении сотрудника из проекта: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- Функция для создания нового проекта с сотрудниками
CREATE OR REPLACE FUNCTION create_project_with_employees(
    p_project_id INT,
    p_project_name VARCHAR(100),
    p_budget DECIMAL(15, 2),
    p_employees JSON DEFAULT '[]'
)
RETURNS TEXT AS $$
DECLARE
    v_employee JSON;
    v_employee_id INT;
    v_role VARCHAR(100);
BEGIN
    -- Проверка корректности бюджета
    IF p_budget < 0 THEN
        RAISE EXCEPTION 'Бюджет не может быть отрицательным';
    END IF;
    
    -- Создание проекта
    INSERT INTO projects (id, name, budget)
    VALUES (p_project_id, p_project_name, p_budget);
    
    -- Логируем создание проекта
    PERFORM log_audit('INSERT', 'projects', p_project_id,
                     NULL, p_project_name || ' (бюджет: ' || p_budget || ')',
                     'Создание нового проекта');
    
    -- Назначение сотрудников, если они предоставлены
    FOR v_employee IN SELECT * FROM json_array_elements(p_employees)
    LOOP
        v_employee_id := (v_employee->>'employee_id')::INT;
        v_role := v_employee->>'role';
        
        PERFORM add_employee_to_project(v_employee_id, p_project_id, v_role);
    END LOOP;
    
    RETURN 'Проект успешно создан с назначенными сотрудниками';
EXCEPTION
    WHEN OTHERS THEN
        RAISE EXCEPTION 'Ошибка при создании проекта: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- Функция для удаления проекта со всеми связанными данными
CREATE OR REPLACE FUNCTION delete_project_cascade(p_project_id INT)
RETURNS TEXT AS $$
DECLARE
    v_project_name VARCHAR(100);
    v_assignment_count INT;
BEGIN
    -- Проверка существования проекта
    SELECT name INTO v_project_name FROM projects WHERE id = p_project_id;
    IF v_project_name IS NULL THEN
        RAISE EXCEPTION 'Проект с ID % не найден', p_project_id;
    END IF;
    
    -- Получаем количество назначений
    SELECT COUNT(*) INTO v_assignment_count 
    FROM employee_projects WHERE project_id = p_project_id;
    
    -- Логируем информацию перед удалением
    PERFORM log_audit('DELETE', 'projects', p_project_id,
                     v_project_name, NULL,
                     'Удаление проекта с ' || v_assignment_count || ' назначениями');
    
    -- Удаляем проект (каскадное удаление назначений через foreign key)
    DELETE FROM projects WHERE id = p_project_id;
    
    RETURN 'Проект успешно удален вместе со всеми назначениями';
EXCEPTION
    WHEN OTHERS THEN
        RAISE EXCEPTION 'Ошибка при удалении проекта: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- Функция для проверки при удалении сотрудника
CREATE OR REPLACE FUNCTION check_employee_deletion()
RETURNS TRIGGER AS $$
DECLARE
    v_project_count INT;
BEGIN
    -- Проверяем, есть ли у сотрудника назначения на проекты
    SELECT COUNT(*) INTO v_project_count 
    FROM employee_projects 
    WHERE employee_id = OLD.id;
    
    IF v_project_count > 0 THEN
        RAISE EXCEPTION 
            'Нельзя удалить сотрудника, назначенного на проекты. ' ||
            'Сначала удалите все его назначения. Найдено назначений: %', 
            v_project_count;
    END IF;
    
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

-- Триггер для проверки удаления сотрудника
CREATE TRIGGER prevent_employee_deletion_with_assignments
BEFORE DELETE ON employees
FOR EACH ROW EXECUTE FUNCTION check_employee_deletion();

-- =============================================
-- 4. ВСТАВКА ТЕСТОВЫХ ДАННЫХ
-- =============================================

-- Вставка тестовых сотрудников
INSERT INTO employees (id, name, position, salary) VALUES
(1, 'Иван Иванов', 'Разработчик', 80000.00),
(2, 'Мария Петрова', 'Менеджер проектов', 95000.00),
(3, 'Алексей Сидоров', 'Аналитик', 75000.00),
(4, 'Елена Васильева', 'Тестировщик', 65000.00),
(5, 'Дмитрий Козлов', 'Разработчик', 85000.00)
ON CONFLICT (id) DO NOTHING;

-- Вставка тестовых проектов
INSERT INTO projects (id, name, budget) VALUES
(1, 'Разработка мобильного приложения', 500000.00),
(2, 'Внедрение CRM системы', 300000.00),
(3, 'Обновление корпоративного портала', 200000.00)
ON CONFLICT (id) DO NOTHING;

-- Вставка тестовых назначений
INSERT INTO employee_projects (employee_id, project_id, role_in_project) VALUES
(1, 1, 'Ведущий разработчик'),
(2, 1, 'Менеджер проекта'),
(3, 1, 'Бизнес-аналитик'),
(4, 1, 'Тестировщик'),
(5, 2, 'Разработчик'),
(2, 2, 'Менеджер проекта'),
(3, 3, 'Аналитик')
ON CONFLICT (employee_id, project_id) DO NOTHING;

-- =============================================
-- 5. ПРИМЕРЫ ИСПОЛЬЗОВАНИЯ (ТРАНЗАКЦИИ)
-- =============================================

-- Пример 1: Обновление бюджета проекта с транзакцией
BEGIN;
SELECT update_project_budget(1, 550000.00);
COMMIT;
-- В случае ошибки: ROLLBACK;

-- Пример 2: Добавление сотрудника в проект с транзакцией
BEGIN;
SELECT add_employee_to_project(4, 2, 'Тестировщик');
COMMIT;

-- Пример 3: Удаление сотрудника из проекта с транзакцией
BEGIN;
SELECT remove_employee_from_project(5, 2);
COMMIT;

-- Пример 4: Создание нового проекта с сотрудниками с транзакцией
BEGIN;
SELECT create_project_with_employees(
    4,
    'Разработка нового сайта',
    400000.00,
    '[{"employee_id": 1, "role": "Архитектор"}, {"employee_id": 2, "role": "Менеджер"}]'
);
COMMIT;

-- Пример 5: Удаление проекта с транзакцией
BEGIN;
SELECT delete_project_cascade(3);
COMMIT;

-- =============================================
-- 6. ПРОВЕРКА ПРАВ ДОСТУПА
-- =============================================

-- Дадим права на выполнение функций соответствующим ролям
GRANT EXECUTE ON FUNCTION update_project_budget TO manager_role, admin_role;
GRANT EXECUTE ON FUNCTION add_employee_to_project TO manager_role, admin_role;
GRANT EXECUTE ON FUNCTION remove_employee_from_project TO manager_role, admin_role;
GRANT EXECUTE ON FUNCTION create_project_with_employees TO manager_role, admin_role;
GRANT EXECUTE ON FUNCTION delete_project_cascade TO admin_role;
GRANT EXECUTE ON FUNCTION log_audit TO admin_role, manager_role;

-- Дадим права на таблицу аудита
GRANT SELECT ON audit_log TO admin_role;
GRANT INSERT ON audit_log TO admin_role, manager_role;

-- =============================================
-- 7. СЦЕНАРИИ ПРОВЕРКИ
-- =============================================

-- Сценарий 4.1: Проверка целостности при удалении сотрудника
-- Попытка удалить сотрудника, который назначен на проекты
BEGIN;
DELETE FROM employees WHERE id = 1; -- Должно вызвать ошибку
COMMIT;

-- Сценарий 5.1: Обработка ошибки при изменении бюджета
BEGIN;
SELECT update_project_budget(1, -1000); -- Отрицательный бюджет, должна быть ошибка
COMMIT;

-- Сценарий 5.2: Ошибка при добавлении несуществующего сотрудника
BEGIN;
SELECT add_employee_to_project(999, 1, 'Разработчик'); -- Несуществующий сотрудник
COMMIT;

-- =============================================
-- 8. ПОЛЕЗНЫЕ ЗАПРОСЫ ДЛЯ ПРОВЕРКИ
-- =============================================

-- Просмотр всех сотрудников
SELECT * FROM employees;

-- Просмотр всех проектов
SELECT * FROM projects;

-- Просмотр всех назначений с именами сотрудников и проектов
SELECT 
    e.name AS employee_name,
    p.name AS project_name,
    ep.role_in_project,
    e.position,
    p.budget
FROM employee_projects ep
JOIN employees e ON e.id = ep.employee_id
JOIN projects p ON p.id = ep.project_id
ORDER BY p.name, e.name;

-- Просмотр логов аудита
SELECT 
    action_time,
    username,
    action_type,
    table_name,
    description
FROM audit_log
ORDER BY action_time DESC
LIMIT 10;

-- Проверка ролей и привилегий
SELECT 
    grantee,
    table_name,
    privilege_type
FROM information_schema.role_table_grants
WHERE table_schema = 'public'
ORDER BY grantee, table_name;
