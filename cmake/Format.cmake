function(Format target directory)
    find_program(CLANG_FORMAT_PATH clang-format)

    if(NOT CLANG_FORMAT_PATH)
        message(FATAL_ERROR "[Format] clang-format not found!")
    endif()

    set(EXPRESSION h hpp hh c cc cxx cpp)
    list(TRANSFORM EXPRESSION PREPEND "${directory}/*.")
    file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
        LIST_DIRECTORIES false ${EXPRESSION}
    )

    add_custom_command(TARGET ${target} PRE_BUILD COMMAND
        ${CLANG_FORMAT_PATH} -i --style=file ${SOURCE_FILES}
    )
endfunction()
