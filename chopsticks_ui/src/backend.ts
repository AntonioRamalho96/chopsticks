import type { GameStatus } from './GameStatus';
import type { MoveType } from './MoveType';

const API_BASE_URL = 'http://127.0.0.1:5000';

/**
 * Reset the game to initial state
 * @param setGameStatus Setter function to update game status
 */
export async function backend_reset(setGameStatus: (status: GameStatus) => void): Promise<void> {
  try {
    const response = await fetch(`${API_BASE_URL}/reset`, {
      method: 'GET',
      headers: {
        'Content-Type': 'application/json',
      },
    });

    if (!response.ok) {
      throw new Error(`Reset failed: ${response.statusText}`);
    }

    const data: GameStatus = await response.json();
    console.log(data);
    setGameStatus(data);
  } catch (error) {
    console.error('Error resetting game:', error);
    throw error;
  }
}

/**
 * Make a player move
 * @param move The move to make (MoveType)
 * @param setGameStatus Setter function to update game status
 */
export async function backend_playerMove(
  move: MoveType,
  setGameStatus: (status: GameStatus) => void
): Promise<void> {
  try {
    const response = await fetch(`${API_BASE_URL}/player_move`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ move }),
    });

    if (!response.ok) {
      const errorData = await response.json().catch(() => ({ error: response.statusText }));
      throw new Error(errorData.error || `Player move failed: ${response.statusText}`);
    }

    const data: GameStatus = await response.json();
    setGameStatus(data);
  } catch (error) {
    console.error('Error making player move:', error);
    throw error;
  }
}

/**
 * Make a computer move
 * @param setGameStatus Setter function to update game status
 */
export async function backend_computerMove(
  setGameStatus: (status: GameStatus) => void
): Promise<void> {
  try {
    const response = await fetch(`${API_BASE_URL}/computer_move`, {
      method: 'GET',
      headers: {
        'Content-Type': 'application/json',
      },
    });

    if (!response.ok) {
      const errorData = await response.json().catch(() => ({ error: response.statusText }));
      throw new Error(errorData.error || `Computer move failed: ${response.statusText}`);
    }

    const data: GameStatus = await response.json();
    setGameStatus(data);
  } catch (error) {
    console.error('Error making computer move:', error);
    throw error;
  }
}

/**
 * Get available moves for the current game state
 * @param setAvailableMoves Setter function to update available moves list
 */
export async function backend_getAvailableMoves(
  setAvailableMoves: (moves: string[]) => void
): Promise<void> {
  try {
    const response = await fetch(`${API_BASE_URL}/available_moves`, {
      method: 'GET',
      headers: {
        'Content-Type': 'application/json',
      },
    });

    if (!response.ok) {
      throw new Error(`Get available moves failed: ${response.statusText}`);
    }

    const data = await response.json();
    // The backend returns {possible_moves: string[]}
    const moves: string[] = data.possible_moves || [];
    setAvailableMoves(moves);
  } catch (error) {
    console.error('Error getting available moves:', error);
    throw error;
  }
}

