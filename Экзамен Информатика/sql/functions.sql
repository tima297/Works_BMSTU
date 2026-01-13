-- Get order status
CREATE OR REPLACE FUNCTION get_order_status(p_order_id INTEGER)
RETURNS VARCHAR AS $$
BEGIN
    RETURN (SELECT status FROM orders WHERE order_id = p_order_id);
END;
$$ LANGUAGE plpgsql;

-- Get user order count
CREATE OR REPLACE FUNCTION get_user_order_count(p_user_id INTEGER)
RETURNS INTEGER AS $$
BEGIN
    RETURN (SELECT COUNT(*) FROM orders WHERE user_id = p_user_id);
END;
$$ LANGUAGE plpgsql;

-- Get total spent by user
CREATE OR REPLACE FUNCTION get_total_spent_by_user(p_user_id INTEGER)
RETURNS DECIMAL AS $$
BEGIN
    RETURN (SELECT COALESCE(SUM(total_price), 0) FROM orders 
            WHERE user_id = p_user_id AND status = 'completed');
END;
$$ LANGUAGE plpgsql;

-- Can return order
CREATE OR REPLACE FUNCTION can_return_order(p_order_id INTEGER)
RETURNS BOOLEAN AS $$
DECLARE
    v_order_date TIMESTAMP;
    v_status VARCHAR;
BEGIN
    SELECT order_date, status INTO v_order_date, v_status 
    FROM orders WHERE order_id = p_order_id;
    
    RETURN (v_status = 'completed' AND 
            (CURRENT_TIMESTAMP - v_order_date) <= INTERVAL '30 days');
END;
$$ LANGUAGE plpgsql;

-- Get order status history
CREATE OR REPLACE FUNCTION get_order_status_history(p_order_id INTEGER)
RETURNS TABLE (history_id INTEGER, old_status VARCHAR, new_status VARCHAR, 
               changed_at TIMESTAMP, changed_by INTEGER) AS $$
BEGIN
    RETURN QUERY
    SELECT order_status_history.history_id, order_status_history.old_status, 
           order_status_history.new_status, order_status_history.changed_at,
           order_status_history.changed_by
    FROM order_status_history
    WHERE order_status_history.order_id = p_order_id
    ORDER BY order_status_history.changed_at ASC;
END;
$$ LANGUAGE plpgsql;

-- Get audit log by user
CREATE OR REPLACE FUNCTION get_audit_log_by_user(p_user_id INTEGER)
RETURNS TABLE (log_id INTEGER, entity_type VARCHAR, entity_id INTEGER, 
               operation VARCHAR, performed_at TIMESTAMP) AS $$
BEGIN
    RETURN QUERY
    SELECT audit_log.log_id, audit_log.entity_type, audit_log.entity_id, 
           audit_log.operation, audit_log.performed_at
    FROM audit_log
    WHERE audit_log.performed_by = p_user_id
    ORDER BY audit_log.performed_at DESC;
END;
$$ LANGUAGE plpgsql;
