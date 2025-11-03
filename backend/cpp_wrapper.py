import ctypes
import pathlib
import json

from game_status import GameStatus


DEFAULT_SO_PATH = pathlib.Path(__file__).parent.parent.joinpath("cpp_core/build/libchopsticks.so")


class CppInterface:
    def __init__(self, dl_path = DEFAULT_SO_PATH):
        self.__inner_lib = ctypes.CDLL(dl_path)
        # Initialize methods I/O types
        self.__init_str_in_str_out_methods()
    
    def make_a_computer_move(self, so_path : str) -> str:
        arg = bytes(so_path, encoding="utf8") 
        return self.__inner_lib.make_a_computer_move(arg).decode("utf8")
    
    def make_a_player_move(self, so_path : str) -> str:
        arg = bytes(so_path, encoding="utf8") 
        return self.__inner_lib.make_a_player_move(arg).decode("utf8")
    
    def get_available_moves(self, so_path : str) -> str:
        arg = bytes(so_path, encoding="utf8") 
        return self.__inner_lib.get_available_moves(arg).decode("utf8")


    # Defining the input and output types for the different methods
    def __init_str_in_str_out_methods(self):
        STR_IN_STR_OUT_METHODS = ["make_a_computer_move",
                                  "make_a_player_move",
                                  "get_available_moves"]
        for method in STR_IN_STR_OUT_METHODS:
            getattr(self.__inner_lib, method).restype = ctypes.c_char_p
            getattr(self.__inner_lib, method).argtypes = [ctypes.c_char_p]


if __name__ == "__main__":
    cpp_interface = CppInterface()

    game_status = GameStatus()
    print(json.dumps(game_status.__dict__))

    # schema = cpp_interface.get_available_moves(str(json.dumps(game_status.__dict__)))
    # print(schema)