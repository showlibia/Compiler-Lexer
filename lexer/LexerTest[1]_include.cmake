if(EXISTS "/home/matrix/Matrixlang/lexer/LexerTest[1]_tests.cmake")
  include("/home/matrix/Matrixlang/lexer/LexerTest[1]_tests.cmake")
else()
  add_test(LexerTest_NOT_BUILT LexerTest_NOT_BUILT)
endif()
