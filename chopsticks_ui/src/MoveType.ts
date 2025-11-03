type MoveType =
  | 'nothing'
  | 'top-left to bottom-left'
  | 'top-left to bottom-right'
  | 'top-right to bottom-left'
  | 'top-right to bottom-right'
  | 'bottom-left to top-left'
  | 'bottom-right to top-left'
  | 'bottom-left to top-right'
  | 'bottom-right to top-right'
  | 'merge top'
  | 'merge bottom';

export type {MoveType};