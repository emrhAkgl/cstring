cmake_minimum_required(VERSION 3.10)
project(MyProject)

# MyString kütüphanesi
add_library(MyString mystring.c)

# Ana uygulama
add_executable(MyApp main.c)

# MyApp'in MyString kütüphanesine bağımlılığı
target_link_libraries(MyApp PRIVATE MyString)
