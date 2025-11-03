export interface ButtonsProps
{
    player_1_turn: boolean,
    possible_moves: string[]

    reset: () => void,
    player_move: (move: string) => void,
    computer_move: () => void,
}