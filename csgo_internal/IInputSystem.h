#pragma once

class IInputSystem
{
public:
	void EnableInput( bool bEnable );
	void ResetInputState();
	bool IsButtonDown( ButtonCode_t code );
	void GetCursorPosition( int* m_pX, int* m_pY );
	ButtonCode_t VirtualKeyToButtonCode( int nVirtualKey );
	int ButtonCodeToVirtualKey( ButtonCode_t code );
};

class CInput2
{
public:
	void* pvftable; //0x00
	bool m_pad_something; //0x04
	bool m_mouse_initialized; //0x05
	bool m_mouse_active; //0x06
	bool pad_something01; //0x07
	char pad_0x08[0x2C]; //0x08
	void* m_keys; //0x34
	char pad_0x38[0x64]; //0x38
	__int32 pad_0x41;
	__int32 pad_0x42;
	bool m_camera_intercepting_mouse; //0x9C
	bool m_cam_in_3rd_person; //0x9D
	bool m_cam_moving_with_mouse; //0x9E
	vector m_camera_offset; //0xA0
	bool m_cam_distance_move; //0xAC
	int m_cam_old_x; //0xB0
	int m_cam_old_y; //0xB4
	int m_cam_x; //0xB8
	int m_cam_y; //0xBC
	bool m_camera_is_orthographic; //0xC0
	vector m_previous_viewangles; //0xC4
	vector m_previous_viewangles_tilt; //0xD0
	float m_last_forward_move; //0xDC
	int m_clear_input_state; //0xE0
	char pad_0xE4[0x8]; //0xE4
	CUserCmd* m_commands;
	void* m_verified_commands; //0xF0
};
