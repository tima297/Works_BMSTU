DROP TABLE IF EXISTS sales ;
DROP TABLE IF EXISTS products ;
DROP TABLE IF EXISTS categories ;

CREATE TABLE categories  (
id INT PRIMARY KEY,
category_name VARCHAR(50)
);

CREATE TABLE products (
id INT PRIMARY KEY,
name VARCHAR(50),
price INT,
quantity INT,
category_id INT,
FOREIGN KEY (category_id) REFERENCES categories(id) 
);


CREATE TABLE sales (
id INT PRIMARY KEY,
product_id INT,
sale_date DATE,
quantity_sold  INT,
FOREIGN KEY (product_id) REFERENCES  products(id) 
);
-- здание 3
INSERT INTO categories (id, category_name) VALUES
(1, 'Электроника'),
(2, 'Одежда'),
(3, 'Книги');

INSERT INTO products (id, name, price, quantity, category_id)
VALUES
(1, 'Смартфон', 50000, 10, 1),
(2, 'Ноутбук', 80000, 5, 1),
(3, 'Футболка', 1500, 50, 2),
(4, 'Джинсы', 3000, 30, 2),
(5, 'Программирование на С++', 1200, 20, 3);
 

INSERT INTO sales (id, product_id, sale_date, quantity_sold) VALUES
(1, 1, '2024-01-15', 2),
(2, 3, '2024-01-16', 5),
(3, 2, '2024-01-17', 1),
(4, 5, '2024-01-18', 3),
(5, 4, '2024-01-19', 2);

-- задание 5
SELECT * 
FROM products
where  quantity < 20;

SELECT 
SUM(s.quantity_sold * p.price) as total_revenue
FROM sales s  
JOIN products p ON s.product_id = p.id
WHERE s.sale_date BETWEEN '2024-01-01' AND '2024-01-31';

SELECT *
FROM products
where category_id = 2;

UPDATE products p
SET quantity = 
    COALESCE(p.quantity, 0) - COALESCE((
        SELECT SUM(quantity_sold)
        FROM sales s
        WHERE s.product_id = p.id), 0);


--задание 6
SELECT 
    c.category_name,
    p.name as product_name,
    SUM(s.quantity_sold) as total_sold,
    SUM(s.quantity_sold * p.price) as total_revenue,
    RANK() OVER (ORDER BY SUM(s.quantity_sold) DESC) as sales_rank
FROM sales s
JOIN products p ON s.product_id = p.id
JOIN categories c ON p.category_id = c.id
GROUP BY c.id, c.category_name, p.id, p.name
ORDER BY total_sold DESC
LIMIT 10;


DELETE FROM sales 
WHERE product_id = 1; 

DELETE FROM products 
WHERE id = 1;