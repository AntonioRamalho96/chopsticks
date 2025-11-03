from game_status import CppMoveType,  MoveType


def get_ui_move(player_1_played: bool, move: CppMoveType) -> MoveType:
    if(player_1_played):
        match move:
            case  "left hand on left hand":
                return  'bottom-left to top-left'
            case "left hand on right hand":
                return  'bottom-left to top-right'
            case "right hand on left hand":
                return  'bottom-right to top-left'
            case "right hand on right hand":
                return  'bottom-right to top-right'
            case "split":
                return "merge bottom"
    else:
        match move:
            case  "left hand on left hand":
                return 'top-left to bottom-left'
            case "left hand on right hand":
                return 'top-left to bottom-right'
            case "right hand on left hand":
                return 'top-right to bottom-left'
            case "right hand on right hand":
                return 'top-right to bottom-right'
            case "split":
                return "merge top"
