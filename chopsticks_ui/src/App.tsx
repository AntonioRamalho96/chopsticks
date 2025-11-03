import { useState } from "react"
import Board from "./Board"
import { defalt_game_status } from "./GameStatus"
import Buttons from "./Buttons";
import {backend_computerMove, backend_playerMove, backend_reset,backend_getAvailableMoves} from "./backend";
import "./App.css"
function App() {

  const [game_status, setGameStatus] = useState(defalt_game_status);
  const [possible_moves, setPossibleMoves] = useState([] as string[]);


  const reset = async () => {
    await backend_reset(setGameStatus);
    await backend_getAvailableMoves(setPossibleMoves);
  };
  const player_move = (move : any) => backend_playerMove(move, setGameStatus);
  const computer_move = async () => {
    await backend_computerMove(setGameStatus);
    await backend_getAvailableMoves(setPossibleMoves);
  };



  return (
    <div className="mainscreen">

     <Board bottomLeft={game_status.BL_hand} 
            bottomRight={game_status.BR_hand} 
            topLeft={game_status.TL_hand} 
            topRight={game_status.TR_hand} 
            last_move={game_status.move} />

     <div className="interaction_pane">

        <Buttons player_1_turn={game_status.player1_plays} 
                  possible_moves={possible_moves}
                  reset={reset}
                  player_move={player_move}
                  computer_move={computer_move}/>
        
        <div>&gt;{game_status.message}</div>
     
      </div>
    </div>
  )
}

export default App
