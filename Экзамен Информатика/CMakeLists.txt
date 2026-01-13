cmake_minimum_required(VERSION 3.10)
project(OnlineStore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find PostgreSQL
find_package(PostgreSQL REQUIRED)

# Include directories
include_directories(${PostgreSQL_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/DatabaseConnection.cpp
    src/User.cpp
    src/Order.cpp
    src/Payment.cpp
    src/Product.cpp
)

# Create executable
add_executable(online_store ${SOURCES})

# Link PostgreSQL libraries
target_link_libraries(online_store ${PostgreSQL_LIBRARIES} pqxx pq)
