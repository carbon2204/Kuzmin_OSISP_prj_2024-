#include <RoboCatPCH.hpp>

unique_ptr<InputManager> InputManager::sInstance;

void InputManager::StaticInit() { sInstance.reset(new InputManager()); }

InputManager::InputManager() : mSelectedNetId(0) {}

void InputManager::Update()
{
    // if we wanted keyboard polling, etc, could do it here
    // but just using SDL event system so no need
}

// void InputManager::HandleInput( EInputAction inInputAction, int inKeyCode )
// {
// 	switch( inKeyCode )
// 	{
// 	case '+':
// 	case '=':
// 		{
// 			float latency = NetworkManager::sInstance->GetSimulatedLatency();
// 			latency += 0.1f;
// 			if( latency > 0.5f )
// 			{
// 				latency = 0.5f;
// 			}
// 			NetworkManager::sInstance->SetSimulatedLatency( latency );
// 			break;
// 		}
// 	case '-':
// 		{
// 			float latency = NetworkManager::sInstance->GetSimulatedLatency();
// 			latency -= 0.1f;
// 			if( latency < 0.0f )
// 			{
// 				latency = 0.0f;
// 			}
// 			NetworkManager::sInstance->SetSimulatedLatency( latency );
// 			break;
// 		}
// 	case SDLK_RETURN:
// 		//start the game!
// 		NetworkManager::sInstance->TryStartGame();
// 		break;
// 	default:
// 		break;
// 	}
// }

// void InputManager::HandleMouseClick( int32_t inX, int32_t inY, uint8_t button )
// {
// 	float worldX = inX / kWorldZoomFactor - kWorldWidth / 2.0f;
// 	float worldY = inY / kWorldZoomFactor - kWorldHeight / 2.0f;
// 	switch( button )
// 	{
// 	case SDL_BUTTON_LEFT:
// 		mSelectedNetId = Board::sInstance->TrySelectGameObject( Vector3( worldX, worldY,
// 0.0f ) ); 		break; 	case SDL_BUTTON_RIGHT: 		GenerateRightClickCommand( Vector3( worldX, worldY, 0.0f
// ) ); 		break; 	default: 		break;
// 	}
// }

void InputManager::GenerateMoveComand(const Vector2 inStartPosition, const Vector2 inEndPosition)
{
    if (mSelectedNetId == 0) { return; }
    if (!Board::sInstance->IsMovePosible(inStartPosition, inEndPosition)) { return; }

    CommandPtr cmd;

    // fallback in case the attack command was invalid
    if (!cmd) { cmd = MoveCommand::StaticCreate(mSelectedNetId, inEndPosition); }

    if (cmd) { mCommandList.AddCommand(cmd); }

    mSelectedNetId = 0;
}

void InputManager::GenerateResignComand()
{
    CommandPtr cmd = ResignCommnad::StaticCreate();

    mCommandList.AddCommand(cmd);
}

void InputManager::HandleMouseClick(Vector2 inBoardPos)
{
    mSelectedNetId = Board::sInstance->TrySelectGameObject(inBoardPos);
}

// TODO : Remake
// void InputManager::GenerateRightClickCommand( const Vector2& inWorldPos )
// {
// 	if ( mSelectedNetId > 0 )
// 	{
// 		//need to figure out if this is an attack or a moveto command
// 		uint32_t targetId = Board::sInstance->TrySelectGameObject( inWorldPos );

// 		CommandPtr cmd;

// 		//fallback in case the attack command was invalid
// 		if ( !cmd )
// 		{
// 			cmd = MoveCommand::StaticCreate( mSelectedNetId, inWorldPos );
// 		}

// 		if ( cmd )
// 		{
// 			mCommandList.AddCommand( cmd );
// 		}
// 	}
// }
