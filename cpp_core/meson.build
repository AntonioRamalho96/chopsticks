project('chopsticks', ['c', 'cpp'])

inc = include_directories('inc')
lib = shared_library(
        'chopsticks', 
        ['src/game.cpp',
         'src/min_max.cpp',
         'src/controller.cpp',
         'src/hands.cpp',
         'src/player_status.cpp',
         'src/play.cpp',
         'src/backend_conversion.cpp',
         'src/game_status.cpp',],
        include_directories : inc,
    )

executable(
  'myapp',
  'tst/command_line_game.cpp',
  include_directories : inc,
  link_with : lib
)

executable(
  'mytest',
  'tst/other_test.cpp',
  include_directories : inc,
  link_with : lib
)
