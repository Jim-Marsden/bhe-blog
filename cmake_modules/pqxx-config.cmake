# cmake_modules/pqxx-config.cmake
if(UNIX)
    set(PQXX /usr/local/include/pqxx)
    find_library(PQXX_LIB pqxx REQUIRED)
    find_library(PQ_LIB pq REQUIRED)
    set(Server_Libraries ${Server_Libraries} libpqxx libpq)

elseif(WIN32)
    set(PQ_ROOT_LIB_DIR ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib)
    set(PQXX_LIB ${PQ_ROOT_LIB_DIR}/libpqxx)
    set(PQ_LIB ${PQ_ROOT_LIB_DIR}/libpq)

    #find_path(PQ_ROOT_LIB_DIR pqxx)
    #find_library(LIBPQXX_LIBRARY libpqxx_static.a REQUIRED)
    #include_directories(${LIBPQXX_INCLUDE_DIR})

    find_library(PQXX_LIB libpqxx.a REQUIRED)
    find_library(PQ_LIB libpq.a REQUIRED)

    link_directories(PQ_ROOT_LIB_DIR)

    set(PQXX_LIBRIARIES ${Server_Libraries} ${PQ_ROOT_LIB_DIR}/libpqxx.lib ${PQ_ROOT_LIB_DIR}/libpq.lib)
    configure_file( ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin/libpqxx.dll libpqxx.dll COPYONLY) # <- [Copy this line with the approprate missing .dll to get it working]

endif()