import { useEffect, useState, useRef } from 'react';
import hand0 from './assets/hand_0.png';
import hand1 from './assets/hand_1.png';
import hand2 from './assets/hand_2.png';
import hand3 from './assets/hand_3.png';
import hand4 from './assets/hand_4.png';
import './Board.css';
import type { MoveType } from './MoveType';
import type { HandNumber } from './HandNumber';

const handImages = [hand0, hand1, hand2, hand3, hand4];



interface BoardProps {
  topLeft: HandNumber;
  topRight: HandNumber;
  bottomLeft: HandNumber;
  bottomRight: HandNumber;
  last_move?: MoveType;
}

function Board({ topLeft, topRight, bottomLeft, bottomRight, last_move = 'nothing' }: BoardProps) {
  const [currentMove, setCurrentMove] = useState<MoveType>('nothing');
  const prevLastMove = useRef(last_move);

  useEffect(() => {
    if (prevLastMove.current !== last_move && last_move !== 'nothing') {
      setCurrentMove(last_move);
      // Reset animation after it completes (2s)
      const timer = setTimeout(() => {
        setCurrentMove('nothing');
      }, 2000);
      prevLastMove.current = last_move;
      return () => clearTimeout(timer);
    }
  }, [last_move]);

  const getAnimationClass = (position: string) => {
    if (currentMove === 'nothing') return '';
    
    // Check if this position is the source of the move
    if (currentMove.startsWith(position)) {
      return `animate-${currentMove.replace(/\s/g, '-')}`;
    }
    
    // For merge animations, check if this position is in the row being merged
    if (currentMove === 'merge top' && (position === 'top-left' || position === 'top-right')) {
      return 'animate-merge-top';
    }
    if (currentMove === 'merge bottom' && (position === 'bottom-left' || position === 'bottom-right')) {
      return 'animate-merge-bottom';
    }
    
    return '';
  };

  return (
    <div className="board">
      <div className="board-row">
        <img 
          src={handImages[topLeft]} 
          alt={`Hand ${topLeft}`}
          className={`hand top-left ${getAnimationClass('top-left')}`}
        />
        <img 
          src={handImages[topRight]} 
          alt={`Hand ${topRight}`}
          className={`hand top-right ${getAnimationClass('top-right')}`}
        />
      </div>
      <div className="board-row bottom-row">
        <img 
          src={handImages[bottomLeft]} 
          alt={`Hand ${bottomLeft}`}
          className={`hand bottom-left ${getAnimationClass('bottom-left')}`}
        />
        <img 
          src={handImages[bottomRight]} 
          alt={`Hand ${bottomRight}`}
          className={`hand bottom-right ${getAnimationClass('bottom-right')}`}
        />
      </div>
    </div>
  );
}

export default Board;

