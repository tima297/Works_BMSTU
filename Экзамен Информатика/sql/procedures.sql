-- Create order procedure
CREATE OR REPLACE PROCEDURE create_order(
    p_user_id INTEGER,
    p_product_ids INTEGER[],
    p_quantities INTEGER[],
    p_user_id_exec INTEGER
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_order_id INTEGER;
    v_i INTEGER;
    v_total_price DECIMAL := 0;
    v_product_price DECIMAL;
BEGIN
    BEGIN
        -- Insert order
        INSERT INTO orders (user_id, status, total_price, order_date)
        VALUES (p_user_id, 'pending', 0, NOW())
        RETURNING order_id INTO v_order_id;
        
        -- Insert order items
        FOR v_i IN 1..array_length(p_product_ids, 1) LOOP
            SELECT price INTO v_product_price FROM products WHERE product_id = p_product_ids[v_i];
            
            INSERT INTO order_items (order_id, product_id, quantity, price)
            VALUES (v_order_id, p_product_ids[v_i], p_quantities[v_i], v_product_price);
            
            v_total_price := v_total_price + (v_product_price * p_quantities[v_i]);
            
            -- Update stock
            UPDATE products SET stock_quantity = stock_quantity - p_quantities[v_i]
            WHERE product_id = p_product_ids[v_i];
        END LOOP;
        
        -- Update order total price
        UPDATE orders SET total_price = v_total_price WHERE order_id = v_order_id;
        
        -- Log in audit
        INSERT INTO audit_log (entity_type, entity_id, operation, performed_by)
        VALUES ('order', v_order_id, 'insert', p_user_id_exec);
        
    EXCEPTION WHEN OTHERS THEN
        RAISE NOTICE 'Error creating order: %', SQLERRM;
        ROLLBACK;
    END;
END;
$$;

-- Update order status procedure
CREATE OR REPLACE PROCEDURE update_order_status(
    p_order_id INTEGER,
    p_new_status VARCHAR,
    p_user_id INTEGER
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_old_status VARCHAR;
BEGIN
    BEGIN
        SELECT status INTO v_old_status FROM orders WHERE order_id = p_order_id;
        
        UPDATE orders SET status = p_new_status WHERE order_id = p_order_id;
        
        INSERT INTO order_status_history (order_id, old_status, new_status, changed_by)
        VALUES (p_order_id, v_old_status, p_new_status, p_user_id);
        
        INSERT INTO audit_log (entity_type, entity_id, operation, performed_by)
        VALUES ('order', p_order_id, 'update', p_user_id);
        
    EXCEPTION WHEN OTHERS THEN
        RAISE NOTICE 'Error updating order status: %', SQLERRM;
        ROLLBACK;
    END;
END;
$$;

-- Approve order procedure
CREATE OR REPLACE PROCEDURE approve_order(
    p_order_id INTEGER,
    p_manager_id INTEGER
)
LANGUAGE plpgsql
AS $$
BEGIN
    CALL update_order_status(p_order_id, 'completed', p_manager_id);
END;
$$;
