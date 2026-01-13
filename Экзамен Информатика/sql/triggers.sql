-- Trigger for updating order_date when status changes
CREATE OR REPLACE FUNCTION update_order_date()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.status <> OLD.status THEN
        NEW.order_date = CURRENT_TIMESTAMP;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER order_status_change_trigger
BEFORE UPDATE ON orders
FOR EACH ROW
EXECUTE FUNCTION update_order_date();

-- Trigger for product price changes
CREATE OR REPLACE FUNCTION update_order_prices_on_product_change()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.price <> OLD.price THEN
        UPDATE order_items SET price = NEW.price
        WHERE product_id = NEW.product_id;
        
        UPDATE orders SET total_price = (
            SELECT SUM(quantity * price) FROM order_items 
            WHERE order_id = orders.order_id
        )
        WHERE order_id IN (
            SELECT order_id FROM order_items WHERE product_id = NEW.product_id
        );
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER product_price_change_trigger
AFTER UPDATE ON products
FOR EACH ROW
EXECUTE FUNCTION update_order_prices_on_product_change();

-- Audit trigger for order changes
CREATE OR REPLACE FUNCTION audit_order_changes()
RETURNS TRIGGER AS $$
BEGIN
    IF TG_OP = 'INSERT' THEN
        INSERT INTO audit_log (entity_type, entity_id, operation, performed_by)
        VALUES ('order', NEW.order_id, 'insert', NEW.user_id);
    ELSIF TG_OP = 'UPDATE' THEN
        INSERT INTO audit_log (entity_type, entity_id, operation, performed_by)
        VALUES ('order', NEW.order_id, 'update', NEW.user_id);
    ELSIF TG_OP = 'DELETE' THEN
        INSERT INTO audit_log (entity_type, entity_id, operation, performed_by)
        VALUES ('order', OLD.order_id, 'delete', OLD.user_id);
    END IF;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER order_audit_trigger
AFTER INSERT OR UPDATE OR DELETE ON orders
FOR EACH ROW
EXECUTE FUNCTION audit_order_changes();
