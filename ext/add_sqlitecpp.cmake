add_subdirectory(${AUDITTOOLS_DIR}/ext/SQLiteCpp)

include_directories(
    ${AUDITTOOLS_DIR}/ext/SQLiteCpp/include
)

set_target_properties( 
    sqlite3 SQLiteCpp SQLiteCpp_cpplint
    PROPERTIES FOLDER ext/sqlitecpp
)

function(config_target_for_sqlitecpp TARGET_NAME)
    target_link_libraries(${TARGET_NAME}
        SQLiteCpp
        sqlite3
        # pthread
        # dl
        )
endfunction()
