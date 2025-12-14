DROP TABLE IF EXISTS sales;
DROP TABLE IF EXISTS products;
DROP TABLE IF EXISTS categories;

CREATE TABLE categories (
    id INT PRIMARY KEY,          
    category_name VARCHAR(100)   
);


CREATE TABLE products (
    id INT PRIMARY KEY,           
    name VARCHAR(150) NOT NULL,   
    price INT,         
    quantity INT DEFAULT 0,      
    category_id INT,   
	
    FOREIGN KEY (category_id) REFERENCES categories(id)
    ON DELETE SET NULL           
    ON UPDATE CASCADE            
);

-- 3. Создание таблицы sales (продажи)
CREATE TABLE sales (
    id INT PRIMARY KEY,          
    product_id INT NOT NULL,     
    sale_date DATE,              
    quantity_sold INT,            
 
    FOREIGN KEY (product_id) REFERENCES products(id)  
	ON DELETE RESTRICT  
    ON UPDATE CASCADE      
);

-- Создадим индексы: 
CREATE INDEX idx_category_name ON categories(category_name);

-- Индекс для ускорения поиска по названию продукта
CREATE INDEX idx_product_name ON products(name);

-- Индекс для ускорения поиска по дате продажи
CREATE INDEX idx_sale_date ON sales(sale_date);

-- Дополнительный составной индекс для часто используемых запросов
CREATE INDEX idx_sales_product_date ON sales(product_id, sale_date);



