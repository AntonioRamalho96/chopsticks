from dataclasses import dataclass
from typing import Literal, Union, Dict, Any
import json

HandNumber = Literal[0, 1, 2, 3, 4]

CppMoveType = Literal[
    "left hand on left hand",
    "left hand on right hand",
    "right hand on left hand",
    "right hand on right hand",
    "split"
]

MoveType = Literal[
    'nothing',
    'top-left to bottom-left',
    'top-left to bottom-right',
    'top-right to bottom-left',
    'top-right to bottom-right',
    'bottom-left to top-left',
    'bottom-right to top-left',
    'bottom-left to top-right',
    'bottom-right to top-right',
    'merge top',
    'merge bottom'
]

@dataclass
class GameStatus:
    """Game status matching the TypeScript GameStatus interface"""
    # Who is playing
    player1_plays: bool = True
    
    # Hands
    TL_hand: HandNumber = 1  # Top left
    TR_hand: HandNumber = 1  # Top right
    BL_hand: HandNumber = 1  # Bottom left
    BR_hand: HandNumber = 1  # Bottom right
    
    # Last move
    move: MoveType = 'nothing'
    move_cpp: CppMoveType = "left hand on left hand"

    score: int = 0
    # Some message from backend
    message: str = ""

    @classmethod
    def from_json(cls, json_data: str) -> 'GameStatus':
        """Create a GameStatus instance from JSON data.
        
        Args:
            json_data: JSON string
            
        Returns:
            A GameStatus instance populated from the JSON data
        """
        # Parse JSON string
        data = json.loads(json_data)
        
        # Extract values with defaults
        result = cls()
        result.player1_plays = data.get('player1_plays', data.get('player1Plays', True))
        result.TL_hand = data.get('TL_hand', 1)
        result.TR_hand = data.get('TR_hand', 1)
        result.BL_hand = data.get('BL_hand', 1)
        result.BR_hand = data.get('BR_hand', 1)
        result.move = data.get('move', data.get('lastMove', data.get('last_move', 'nothing')))
        result.move_cpp = data.get('move_cpp', "left hand on left hand")
        result.score = data.get('score', 0)
        result.message = data.get('message', 'Lets play!')
        
        return result
        

