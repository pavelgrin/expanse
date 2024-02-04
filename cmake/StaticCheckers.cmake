function(AddStaticCheckers target)
    find_program(CPPCHECK_PATH cppcheck)

    # [TODO] Update CMake to version 3.3 to use iwyu
    # find_program(IWYU_PATH NAMES include-what-you-use iwyu)

    if(NOT CPPCHECK_PATH)
        message(FATAL_ERROR "[AddStaticCheckers] cppcheck not found!")
    # elseif(NOT IWYU_PATH)
    #     message(FATAL_ERROR "[AddStaticCheckers] include-what-you-use not found!")
    endif()

    set_target_properties(${target}
        PROPERTIES CXX_CPPCHECK
        "${CPPCHECK_PATH};--inline-suppr;--enable=warning;--error-exitcode=10"
    )

    # set_target_properties(${target} PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})
endfunction()
