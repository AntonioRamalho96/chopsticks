import type { HandNumber } from "./HandNumber";
import type { MoveType } from "./MoveType";

export interface GameStatus {
  // Who is playing
  player1_plays: boolean;

  // Hands
  TL_hand: HandNumber;
  TR_hand: HandNumber;
  BL_hand: HandNumber;
  BR_hand: HandNumber;

  // Last move
  move: MoveType;

  // Some message from backend
  message: string;
}

export const defalt_game_status : GameStatus= {
  player1_plays : true,
  TL_hand : 0,
  TR_hand : 0,
  BL_hand : 0,
  BR_hand : 0,
  move : "nothing",
  message : "Lets play"
}
