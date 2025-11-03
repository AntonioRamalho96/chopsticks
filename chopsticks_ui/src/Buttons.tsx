import type { ButtonsProps } from "./ButtonsProps";
import "./Buttons.css"


function Buttons(props: ButtonsProps)
{

    const call_move = (move : string) =>
    {
        console.log("Calling with move")
        console.log(move);
        return () => props.player_move(move);
    }


    return (<div className="button_bar">
        <button className="action_button" onClick={props.reset} >Reset</button>
        {props.player_1_turn ? 
            <>
                {props.possible_moves.map((move: string) =>
                <button className="action_button" onClick={call_move(move)} >{move}</button>)}
            </>
        :
            <button className="action_button" onClick={props.computer_move}>computer move</button>
        }
    </div>);
}

export default Buttons;