function(AddCppCheck target)
    find_program(CPPCHECK_PATH cppcheck)

    if(NOT CPPCHECK_PATH)
        message(FATAL_ERROR "[AddCppCheck] cppcheck not found!")
    endif()

    set_target_properties(${target}
        PROPERTIES CXX_CPPCHECK
        "${CPPCHECK_PATH};--inline-suppr;--enable=warning;--error-exitcode=10"
    )
endfunction()
