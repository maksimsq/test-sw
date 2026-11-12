-- Physical schema for SliderAR
CREATE TABLE camera (
    camera_id INT PRIMARY KEY,
    resolution VARCHAR(50) NOT NULL CHECK (resolution ~ '^[0-9]+x[0-9]+$'),
    frame_rate INT NOT NULL CHECK (frame_rate > 0 AND frame_rate <= 120)
);

CREATE TABLE aruco_marker (
    marker_id INT PRIMARY KEY,
    size FLOAT NOT NULL CHECK (size > 0.0),
    camera_id INT NOT NULL,
    FOREIGN KEY (camera_id) REFERENCES camera (camera_id)
    ON DELETE CASCADE
);

CREATE TABLE slider_controller (
    slider_id INT PRIMARY KEY,
    current_value FLOAT NOT NULL CHECK (
        current_value >= 0.0 AND current_value <= 100.0
    ),
    state VARCHAR(20) NOT NULL CHECK (
        state IN ('ACTIVE', 'LOST', 'CALIBRATING')
    ),
    marker_id INT NOT NULL,
    FOREIGN KEY (marker_id) REFERENCES aruco_marker (marker_id)
    ON DELETE CASCADE
);

CREATE TABLE calibration (
    calibration_id INT PRIMARY KEY,
    min_value FLOAT NOT NULL CHECK (min_value >= 0.0),
    max_value FLOAT NOT NULL CHECK (max_value > min_value),
    calibration_date DATE NOT NULL,
    slider_id INT NOT NULL,
    FOREIGN KEY (slider_id) REFERENCES slider_controller (slider_id)
    ON DELETE CASCADE
);

CREATE TABLE system_config (
    config_id INT PRIMARY KEY,
    config_name VARCHAR(100) NOT NULL CHECK (
        config_name ~ '^[A-Za-z0-9 _-]+$'
    ),
    status VARCHAR(20) NOT NULL CHECK (
        status IN ('READY', 'UNSYNCHRONIZED', 'ERROR')
    ),
    calibration_id INT NOT NULL,
    FOREIGN KEY (calibration_id) REFERENCES calibration (calibration_id)
    ON DELETE CASCADE
);
