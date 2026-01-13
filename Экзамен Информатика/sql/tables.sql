-- Create users table
CREATE TABLE users (
    user_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    role VARCHAR(50) CHECK (role IN ('admin', 'manager', 'customer')),
    password_hash VARCHAR(255) NOT NULL,
    loyalty_level INTEGER DEFAULT 0 CHECK (loyalty_level IN (0, 1))
);

-- Create products table
CREATE TABLE products (
    product_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    price DECIMAL(10, 2) CHECK (price > 0),
    stock_quantity INTEGER DEFAULT 0 CHECK (stock_quantity >= 0)
);

-- Create orders table
CREATE TABLE orders (
    order_id SERIAL PRIMARY KEY,
    user_id INTEGER NOT NULL,
    status VARCHAR(50) DEFAULT 'pending' CHECK (status IN ('pending', 'completed', 'canceled', 'returned')),
    total_price DECIMAL(10, 2),
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

-- Create order_items table
CREATE TABLE order_items (
    order_item_id SERIAL PRIMARY KEY,
    order_id INTEGER NOT NULL,
    product_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    price DECIMAL(10, 2),
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(product_id)
);

-- Create order_status_history table
CREATE TABLE order_status_history (
    history_id SERIAL PRIMARY KEY,
    order_id INTEGER NOT NULL,
    old_status VARCHAR(50),
    new_status VARCHAR(50),
    changed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    changed_by INTEGER NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id),
    FOREIGN KEY (changed_by) REFERENCES users(user_id)
);

-- Create audit_log table
CREATE TABLE audit_log (
    log_id SERIAL PRIMARY KEY,
    entity_type VARCHAR(50) CHECK (entity_type IN ('order', 'product', 'user')),
    entity_id INTEGER NOT NULL,
    operation VARCHAR(50) CHECK (operation IN ('insert', 'update', 'delete')),
    performed_by INTEGER NOT NULL,
    performed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (performed_by) REFERENCES users(user_id)
);
