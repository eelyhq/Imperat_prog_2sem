cmake_minimum_required(VERSION 3.20)
project(UniversityLabs C)

# --- Настройки стандартов и компилятора ---
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Включаем полезные предупреждения (Warnings) для отлова ошибок
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- 12 Pack  ---
add_executable(Lab12_Task4  12_pack/4.c)
add_executable(Lab12_Task5  12_pack/5.c)
add_executable(Lab12_Task6  12_pack/6.c)
add_executable(Lab12_Task7  12_pack/7.c)

# --- 13 Pack ---
add_executable(Lab13_Task1  13_pack/1.c)
add_executable(Lab13_Task2  13_pack/2.c)
add_executable(Lab13_Task3  13_pack/3.c)
add_executable(Lab13_Task4  13_pack/4.c)
add_executable(Lab13_Task5  13_pack/5.c)
add_executable(Lab13_Task6  13_pack/6.c)
add_executable(Lab13_Task7  13_pack/7.c)
add_executable(Lab13_Task8  13_pack/8.c)
add_executable(Lab13_Task9  13_pack/9.c)
add_executable(Lab13_Task10  13_pack/10.c)
target_link_libraries(Lab13_Task10 m)
add_executable(Lab13_Task11  13_pack/11.c)




# --- 14 Pack ---
add_executable(Lab14_Task1  14_pack/1.c)
add_executable(Lab14_Task3  14_pack/3.c)
add_executable(Lab14_Task5  14_pack/5/main.c)
add_executable(Lab14_Task4-1  14_pack/4/main.c)
add_executable(Lab14_Task4-2 14_pack/4/sum.c)
add_executable(Lab14_Task4-3  14_pack/4/query.c)
add_executable(Lab14_Task6  14_pack/6.c)
add_executable(Lab14_Task7  14_pack/7/main.c)



# --- 15 Pack ---
add_executable(Lab15_Task1-1  15_pack/1/level1.c)
add_executable(Lab15_Task1-2  15_pack/1/level2.c)
add_executable(Lab15_Task1-3  15_pack/1/level3.c)
add_executable(Lab15_Task3  15_pack/3.c)
add_executable(Lab15_Task4  15_pack/4.c)
target_link_libraries(Lab15_Task4 m)

# --- 16 Pack ---
add_executable(Lab16_Task1  16_pack/1/test.c 16_pack/1/integerset.c)
add_executable(Lab16_Task2  16_pack/2/main.c)
add_executable(Lab16_Task3  16_pack/3/main.c)
add_executable(Lab16_Task4  16_pack/4/main.c)

# Создаем цель Lab16_Task5 из myasm.c
add_executable(Lab16_Task5  16_pack/5/myasm.c)
# Линкуем dl именно к Lab16_Task5 !
target_link_libraries(Lab16_Task5 dl)

# --- 2. ПЛАГИН CORE ---
add_library(core SHARED "16_pack/5/core.c")
set_target_properties(core PROPERTIES PREFIX "")

# --- 3. ПЛАГИН STRING ---
add_library(string SHARED "16_pack/5/string.c")
set_target_properties(string PROPERTIES PREFIX "")

add_dependencies(Lab16_Task5 core string)

add_executable(Lab16_Task6  16_pack/6/main.c)


# --- 16 Pack ---
add_executable(Lab17_Task1 17_pack/1.c)
add_executable(Lab17_Task2 17_pack/2.c)
add_executable(Lab17_Task3 17_pack/3.c)
add_executable(Lab17_Task4 17_pack/4.c)
add_executable(Lab17_Task5 17_pack/5.c)
add_executable(Lab17_Task6 17_pack/6.c)


# --- Линковка библиотек ---
# Подключаем математическую библиотеку (libm) для задачи, где она нужна
target_link_libraries(Lab13_Task2 PRIVATE m)