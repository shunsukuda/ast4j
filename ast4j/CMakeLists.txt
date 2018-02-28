add_executable(
    astr4j 
        "src/astr4j.cpp"
)

#execute_process(
#    WORKING_DIRECTORY src
    #COMMAND rm -f *.o lex.yy.c y.tab.*
    #COMMAND flex --header-file=lex.yy.h lexer.l
    #COMMAND bison -dy parser.y
#)