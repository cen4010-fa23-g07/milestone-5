#pragma once
// gui test program for milestone
// gui code based of microsoft documentation
// application for windows
// https://learn.microsoft.com/en-us/cpp/windows/overview-of-windows-programming-in-cpp?view=msvc-170
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/learn-to-program-for-windows

// header files contains all 3rd party and custom classes/functions
#include "components.h"


// !! graphics are current implemented via windows GDI. this isn't beutiful, but its 
// !! the simplest to implement. this could be subject to change, but it isn't nessasary.



// required for creating window
static TCHAR szWindowClass[] = _T("CleverCalc");
static TCHAR szTitle[] = _T("CleverCalc equation solver.");

const static TCHAR clear[] = { '\0' };

std::string const static UL = "users.list";

const static int W_WIDTH = 900; // window width
const static int W_HIGHT = 900; // window hight
const static int W_CENTER = 450;
const static int W_SPACING = 5;
const static int TCHAR_MAX = 500;
const static int TCHAR_SMALL = 100;

// Application State https://learn.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-/
// this struct defines what will qualify as state information
struct StateInfo {
	enum page { home, createAcc, forgotPass, mainMenu, linAlgebra, sysEquations, stats }; // current application page
	page currentPage = home;
	// TODO, add more info as need.
	// fod example: user login info.
	std::vector<std::string> currentProblem;
	int currentUser = 0;
};

//void update



// !! these are the windows creation, hideing, and drawing functions

// START: HOMEPAGE
// draws the home page when called from WM_PAINT
void DrawHomePage(	HDC hdc , _In_ HWND   hWnd)
{
	TCHAR CCtitle[] = _T("CleverCalc");
	RECT title;
	title.left = 0;
	title.top = 20;
	title.right = W_WIDTH;
	title.bottom = 40; //900x900 is the window size. TODO: make this dynamic. even tho window size wont change from user, this will make it easy if we want to change the default size.
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		CCtitle,// text
		(-1), // text length -1 to find null terminator
		&title, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);


	RECT username;
	username.left = 0;
	username.top = 45;
	username.right = W_WIDTH;
	username.bottom = 65;
	TCHAR text_username[] = _T("Username:");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_username,// text
		(-1), // text length -1 to find null terminator
		&username, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);
	
	RECT password;
	password.left = 0;
	password.top = 95;
	password.right = W_WIDTH;
	password.bottom = 115;
	TCHAR text_password[] = _T("Password:");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_password,// text
		(-1), // text length -1 to find null terminator
		&password, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);


	// display buttons and text fields

	HWND usernameWnd = FindWindowExW(hWnd, NULL, NULL, NULL);
	
	ShowWindow(usernameWnd, // window handle
		SW_NORMAL); 
	UpdateWindow(usernameWnd);

	HWND passwordWnd = FindWindowExW(hWnd, usernameWnd, NULL, NULL);
	
	ShowWindow(passwordWnd, // window handle
		SW_NORMAL); 
	UpdateWindow(passwordWnd);

	HWND forgotWnd = FindWindowExW(hWnd, passwordWnd, NULL, NULL);
	
	ShowWindow(forgotWnd, // window handle
		SW_NORMAL); 
	UpdateWindow(forgotWnd);

	HWND loginWnd = FindWindowExW(hWnd, forgotWnd, NULL, NULL);
	ShowWindow(loginWnd, // window handle
		SW_NORMAL); 

	HWND registertWnd = FindWindowExW(hWnd, loginWnd, NULL, NULL);
	ShowWindow(registertWnd, // window handle
		SW_NORMAL);

	UpdateWindow(loginWnd);
	UpdateWindow(hWnd);
}

// creates windows needed to display home page.
void CreateHomeWnds(HWND hWnd, _In_ int nCmdShow)
{
	// text box https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowa
	int inputWidth = 300;
	int inputHight = 20;
	HWND usernameWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_EDIT, // EDIT cos its a text box
		NULL, // text in text box
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (inputWidth / 2)), // center
		70, // TODO: something cleaner
		inputWidth,
		inputHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// password box
	HWND passwordWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_EDIT, // EDIT cos its a text box
		NULL, // text in text box
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (inputWidth / 2)), // center
		120, // TODO: something cleaner
		inputWidth,
		inputHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// make it so it shows a password char.

	Edit_SetPasswordChar(
		passwordWnd,
		'*'
	);

	// buttons
	int buttonWidth = 140;
	int buttonHight = 20;


	// forgot account

	static TCHAR CCforgot[] = _T("Forgot Pass");
	HWND forgotWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCforgot, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (buttonWidth + 5)), // left of center
		145, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// login
	static TCHAR CClogin[] = _T("Login");
	HWND loginWnd = CreateWindowExW(

		WS_EX_LEFT,
		WC_BUTTON, // button
		CClogin, // text in button
		WS_BORDER | WS_CHILD, // style
		((W_WIDTH / 2) + 5), // right of center
		145, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// register
	static TCHAR CCregister[] = _T("Register");
	HWND registerWnd = CreateWindowExW(

		WS_EX_LEFT,
		WC_BUTTON, // button
		CCregister, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_WIDTH / 2) - (buttonWidth / 2), //center
		170, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// TODO: make it so no more copy pasting this command

	
	ShowWindow(usernameWnd, // window handle
		nCmdShow); 
	UpdateWindow(usernameWnd);

	
	ShowWindow(passwordWnd, // window handle
		nCmdShow); 
	UpdateWindow(passwordWnd);

	
	ShowWindow(forgotWnd, // window handle
		nCmdShow); 
	UpdateWindow(forgotWnd);

	
	ShowWindow(loginWnd, // window handle
		nCmdShow); 
	UpdateWindow(loginWnd);

	
	ShowWindow(registerWnd, // window handle
		nCmdShow); 
	UpdateWindow(registerWnd);

	// make window hidden
	ShowWindow(usernameWnd, // window handle
		SW_HIDE); 
	UpdateWindow(usernameWnd);

	// make window hidden
	ShowWindow(passwordWnd, // window handle
		SW_HIDE); 
	UpdateWindow(passwordWnd);

	// make window hidden
	ShowWindow(forgotWnd, // window handle
		SW_HIDE); 
	UpdateWindow(forgotWnd);

	// make window hidden
	ShowWindow(loginWnd, // window handle
		SW_HIDE); 
	UpdateWindow(loginWnd);

	// make window hidden
	ShowWindow(registerWnd, // window handle
		SW_HIDE);
	UpdateWindow(registerWnd);

	UpdateWindow(hWnd);
}

// hides homepage windows
void HideHomePage(_In_ HWND   hWnd)
{
	HWND usernameWnd = FindWindowExW(hWnd, NULL, NULL, NULL);
	SetWindowTextW(usernameWnd, clear);
	ShowWindow(usernameWnd, // window handle
		SW_HIDE); 
	UpdateWindow(usernameWnd);

	HWND passwordWnd = FindWindowExW(hWnd, usernameWnd, NULL, NULL);
	SetWindowTextW(passwordWnd, clear);
	ShowWindow(passwordWnd, // window handle
		SW_HIDE); 
	UpdateWindow(passwordWnd);

	HWND forgotWnd = FindWindowExW(hWnd, passwordWnd, NULL, NULL);
	
	ShowWindow(forgotWnd, // window handle
		SW_HIDE); 
	UpdateWindow(forgotWnd);

	HWND loginWnd = FindWindowExW(hWnd, forgotWnd, NULL, NULL);
	
	ShowWindow(loginWnd, // window handle
		SW_HIDE); 

	HWND registertWnd = FindWindowExW(hWnd, loginWnd, NULL, NULL);
	
	ShowWindow(registertWnd, // window handle
		SW_HIDE);

	UpdateWindow(registertWnd);

	UpdateWindow(loginWnd);
	UpdateWindow(hWnd);
}
// END: HOMEPAGE

// START: Create Account
// draws the register page when called from WM_PAINT
void DrawRegister(HDC hdc, _In_ HWND   hWnd)
{
	TCHAR CCtitle[] = _T("CleverCalc");
	RECT title;
	title.left = 0;
	title.top = 20;
	title.right = W_WIDTH;
	title.bottom = 40; 
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		CCtitle,// text
		(-1), // text length -1 to find null terminator
		&title, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);

	RECT email;
	email.left = 0;
	email.top = 45;
	email.right = W_WIDTH;
	email.bottom = 65;
	TCHAR text_email[] = _T("Email:");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_email,// text
		(-1), // text length -1 to find null terminator
		&email, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);

	RECT username;
	username.left = 0;
	username.top = 90;
	username.right = W_WIDTH;
	username.bottom = 110;
	TCHAR text_username[] = _T("Username:");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_username,// text
		(-1), // text length -1 to find null terminator
		&username, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);

	RECT password;
	password.left = 0;
	password.top = 135;
	password.right = W_WIDTH;
	password.bottom = 155;
	TCHAR text_password[] = _T("Password:");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_password,// text
		(-1), // text length -1 to find null terminator
		&password, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);

	RECT password2;
	password2.left = 0;
	password2.top = 180;
	password2.right = W_WIDTH;
	password2.bottom = 200;
	TCHAR text_password2[] = _T("Re-Enter Password:");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_password2,// text
		(-1), // text length -1 to find null terminator
		&password2, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);


	// display buttons and text fields

	TCHAR CCregister[] = _T("reg");
	HWND regWnd = FindWindowExW(hWnd, NULL, NULL, CCregister);

	HWND emailWnd = FindWindowExW(hWnd, regWnd, NULL, NULL);
	
	ShowWindow(emailWnd, // window handle
		SW_NORMAL);
	UpdateWindow(emailWnd);

	HWND usernameWnd = FindWindowExW(hWnd, emailWnd, NULL, NULL);
	
	ShowWindow(usernameWnd, // window handle
		SW_NORMAL);
	UpdateWindow(usernameWnd);

	HWND passwordWnd = FindWindowExW(hWnd, usernameWnd, NULL, NULL);
	
	ShowWindow(passwordWnd, // window handle
		SW_NORMAL);
	UpdateWindow(passwordWnd);

	HWND password2Wnd = FindWindowExW(hWnd, passwordWnd, NULL, NULL);
	
	ShowWindow(password2Wnd, // window handle
		SW_NORMAL);
	UpdateWindow(password2Wnd);

	HWND registerWnd = FindWindowExW(hWnd, password2Wnd, NULL, NULL);
	
	ShowWindow(registerWnd, // window handle
		SW_NORMAL);
	UpdateWindow(registerWnd);
	UpdateWindow(hWnd);
	UpdateWindow(hWnd);
}

// creates windows needed to display Register page.
void CreateRegisterWnds(HWND hWnd, _In_ int nCmdShow)
{
	// probably bad practice: a blank empty window with a searchable title so when finding windows from the draw function, we can start from this point.
	TCHAR CCregister[] = _T("reg");
	CreateWindowExW(
		WS_EX_LEFT,
		WC_STATIC,
		CCregister,
		WS_CHILD,
		0,
		0,
		0,
		0,
		hWnd,
		NULL,
		NULL,
		NULL
	);



	// text box https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowa
	int inputWidth = 300;
	int inputHight = 20;


	HWND emailWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_EDIT, // EDIT cos its a text box
		NULL, // text in text box
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (inputWidth / 2)), // center
		70, // TODO: something cleaner
		inputWidth,
		inputHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	HWND usernameWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_EDIT, // EDIT cos its a text box
		NULL, // text in text box
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (inputWidth / 2)), // center
		115, // TODO: something cleaner
		inputWidth,
		inputHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// password box
	HWND passwordWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_EDIT, // EDIT cos its a text box
		NULL, // text in text box
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (inputWidth / 2)), // center
		160, // TODO: something cleaner
		inputWidth,
		inputHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// make it so it shows a password char.

	Edit_SetPasswordChar(
		passwordWnd,
		'*'
	);

	// password box
	HWND password2Wnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_EDIT, // EDIT cos its a text box
		NULL, // text in text box
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (inputWidth / 2)), // center
		205, // TODO: something cleaner
		inputWidth,
		inputHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// make it so it shows a password char.

	Edit_SetPasswordChar(
		password2Wnd,
		'*'
	);

	// buttons
	int buttonWidth = 140;
	int buttonHight = 20;


	// create account

	static TCHAR CCaccount[] = _T("Create Account");
	HWND create_accountWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCaccount, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (buttonWidth /2)), // left of center
		230, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	
	ShowWindow(emailWnd, // window handle
		nCmdShow); 
	UpdateWindow(emailWnd);

	
	ShowWindow(usernameWnd, // window handle
		nCmdShow); 
	UpdateWindow(usernameWnd);

	
	ShowWindow(passwordWnd, // window handle
		nCmdShow); 
	UpdateWindow(passwordWnd);

	
	ShowWindow(password2Wnd, // window handle
		nCmdShow); 
	UpdateWindow(password2Wnd);

	
	ShowWindow(create_accountWnd, // window handle
		nCmdShow); 
	UpdateWindow(create_accountWnd);

	// make window hidden
	ShowWindow(emailWnd, // window handle
		SW_HIDE);
	UpdateWindow(emailWnd);

	// make window hidden
	ShowWindow(usernameWnd, // window handle
		SW_HIDE); 
	UpdateWindow(usernameWnd);

	// make window hidden
	ShowWindow(passwordWnd, // window handle
		SW_HIDE); 
	UpdateWindow(passwordWnd);

	// make window hidden
	ShowWindow(password2Wnd, // window handle
		SW_HIDE);
	UpdateWindow(password2Wnd);

	// make window hidden
	ShowWindow(create_accountWnd, // window handle
		SW_HIDE); 
	UpdateWindow(create_accountWnd);

	UpdateWindow(hWnd);
}

// hides Register windows
void HideRegister(_In_ HWND   hWnd)
{
	TCHAR CCregister[] = _T("reg");
	HWND regWnd = FindWindowExW(hWnd, NULL, NULL, CCregister);
	
	HWND emailWnd = FindWindowExW(hWnd, regWnd, NULL, NULL);
	SetWindowTextW(emailWnd, clear);
	ShowWindow(emailWnd, // window handle
		SW_HIDE);
	UpdateWindow(emailWnd);

	HWND usernameWnd = FindWindowExW(hWnd, emailWnd, NULL, NULL);
	SetWindowTextW(usernameWnd, clear);
	ShowWindow(usernameWnd, // window handle
		SW_HIDE); 
	UpdateWindow(usernameWnd);

	HWND passwordWnd = FindWindowExW(hWnd, usernameWnd, NULL, NULL);
	SetWindowTextW(passwordWnd, clear);
	ShowWindow(passwordWnd, // window handle
		SW_HIDE); 
	UpdateWindow(passwordWnd);

	HWND password2Wnd = FindWindowExW(hWnd, passwordWnd, NULL, NULL);
	SetWindowTextW(password2Wnd, clear);
	ShowWindow(password2Wnd, // window handle
		SW_HIDE);
	UpdateWindow(password2Wnd);

	HWND registerWnd = FindWindowExW(hWnd, password2Wnd, NULL, NULL);
	
	ShowWindow(registerWnd, // window handle
		SW_HIDE); 
	UpdateWindow(registerWnd);
	UpdateWindow(hWnd);
}
// END: Register

// START: Forgot Password
// draws the Forgot page when called from WM_PAINT
void DrawForgot(HDC hdc, _In_ HWND   hWnd)
{
	TCHAR CCtitle[] = _T("CleverCalc");
	RECT title;
	title.left = 0;
	title.top = 20;
	title.right = W_WIDTH;
	title.bottom = 40; //900x900 is the window size. TODO: make this dynamic. even tho window size wont change from user, this will make it easy if we want to change the default size.
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		CCtitle,// text
		(-1), // text length -1 to find null terminator
		&title, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);


	RECT username;
	username.left = 0;
	username.top = 45;
	username.right = W_WIDTH;
	username.bottom = 65;
	TCHAR text_username[] = _T("Username:");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_username,// text
		(-1), // text length -1 to find null terminator
		&username, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);

	RECT email;
	email.left = 0;
	email.top = 95;
	email.right = W_WIDTH;
	email.bottom = 115;
	TCHAR text_email[] = _T("Email:");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_email,// text
		(-1), // text length -1 to find null terminator
		&email, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);

	RECT passwrd;
	passwrd.left = 0;
	passwrd.top = 145;
	passwrd.right = W_WIDTH;
	passwrd.bottom = 165;
	TCHAR text_passwrd[] = _T("New Password:");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_passwrd,// text
		(-1), // text length -1 to find null terminator
		&passwrd, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);


	// display buttons and text fields
	TCHAR forgot[] = _T("forgot");
	HWND forgotWnd = FindWindowExW(hWnd, NULL, NULL, forgot);

	HWND usernameWnd = FindWindowExW(hWnd, forgotWnd, NULL, NULL);
	
	ShowWindow(usernameWnd, // window handle
		SW_NORMAL);
	UpdateWindow(usernameWnd);

	HWND emailWnd = FindWindowExW(hWnd, usernameWnd, NULL, NULL);
	
	ShowWindow(emailWnd, // window handle
		SW_NORMAL);
	UpdateWindow(emailWnd);

	//passWnd
	HWND passWnd = FindWindowExW(hWnd, emailWnd, NULL, NULL);

	ShowWindow(passWnd, // window handle
		SW_NORMAL);
	UpdateWindow(passWnd);


	HWND recoverWnd = FindWindowExW(hWnd, passWnd, NULL, NULL);
	
	ShowWindow(recoverWnd, // window handle
		SW_NORMAL);
	UpdateWindow(recoverWnd);
	UpdateWindow(hWnd);
}

// creates windows needed to display Forgot page.
void CreateForgotWnds(HWND hWnd, _In_ int nCmdShow)
{
	// probably bad practice: a blank empty window with a searchable title so when finding windows from the draw function, we can start from this point.
	TCHAR CCregister[] = _T("forgot");
	CreateWindowExW(
		WS_EX_LEFT,
		WC_STATIC,
		CCregister,
		WS_CHILD,
		0,
		0,
		0,
		0,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// text box https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowa
	int inputWidth = 300;
	int inputHight = 20;
	HWND usernameWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_EDIT, // EDIT cos its a text box
		NULL, // text in text box
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (inputWidth / 2)), // center
		70, // TODO: something cleaner
		inputWidth,
		inputHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// email box
	HWND emailWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_EDIT, // EDIT cos its a text box
		NULL, // text in text box
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (inputWidth / 2)), // center
		120, // TODO: something cleaner
		inputWidth,
		inputHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// newpass box
	HWND passWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_EDIT, // EDIT cos its a text box
		NULL, // text in text box
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (inputWidth / 2)), // center
		170, // TODO: something cleaner
		inputWidth,
		inputHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	Edit_SetPasswordChar(
		passWnd,
		'*'
	);

	// buttons
	int buttonWidth = 140;
	int buttonHight = 20;


	// recover account

	static TCHAR CCrecover[] = _T("Recover Account");
	HWND recoverWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCrecover, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (buttonWidth / 2)), // left of center
		195, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);



	// TODO: make it so no more copy pasting this command

	

	
	ShowWindow(usernameWnd, // window handle
		nCmdShow);
	UpdateWindow(usernameWnd);

	
	ShowWindow(emailWnd, // window handle
		nCmdShow);
	UpdateWindow(emailWnd);

	ShowWindow(passWnd, // window handle
		nCmdShow);
	UpdateWindow(passWnd);
	
	ShowWindow(recoverWnd, // window handle
		nCmdShow);
	UpdateWindow(recoverWnd);


	// make window hidden
	ShowWindow(usernameWnd, // window handle
		SW_HIDE);
	UpdateWindow(usernameWnd);

	ShowWindow(emailWnd, // window handle
		SW_HIDE);
	UpdateWindow(emailWnd);

	ShowWindow(passWnd, // window handle
		SW_HIDE);
	UpdateWindow(passWnd);

	ShowWindow(recoverWnd, // window handle
		SW_HIDE);
	UpdateWindow(recoverWnd);

	UpdateWindow(hWnd);
}

// hides Forgot windows
void HideForgot(_In_ HWND   hWnd)
{
	TCHAR forgot[] = _T("forgot");
	HWND forgotWnd = FindWindowExW(hWnd, NULL, NULL, forgot);

	HWND usernameWnd = FindWindowExW(hWnd, forgotWnd, NULL, NULL);
	SetWindowTextW(usernameWnd, clear);
	ShowWindow(usernameWnd, // window handle
		SW_HIDE);
	UpdateWindow(usernameWnd);

	HWND emailWnd = FindWindowExW(hWnd, usernameWnd, NULL, NULL);
	SetWindowTextW(emailWnd, clear);
	ShowWindow(emailWnd, // window handle
		SW_HIDE);
	UpdateWindow(emailWnd);
	
	//passWnd
	HWND passWnd = FindWindowExW(hWnd, emailWnd, NULL, NULL);
	SetWindowTextW(passWnd, clear);
	ShowWindow(passWnd, // window handle
		SW_HIDE);
	UpdateWindow(passWnd);


	HWND recoverWnd = FindWindowExW(hWnd, passWnd, NULL, NULL);
	
	ShowWindow(recoverWnd, // window handle
		SW_HIDE);
	UpdateWindow(recoverWnd);
	UpdateWindow(hWnd);
}
// END: HOMEPAGE

// START: Main Menu
// draws the main menu when called from WM_PAINT
void DrawMainMenu(HDC hdc, _In_ HWND   hWnd)
{

	TCHAR CCtitle[] = _T("CleverCalc");
	RECT title;
	title.left = 0;
	title.top = 20;
	title.right = W_WIDTH;
	title.bottom = 40;
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		CCtitle,// text
		(-1), // text length -1 to find null terminator
		&title, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);

	// display buttons and text fields

	TCHAR mainmenu[] = _T("mainmenu");
	HWND mainmenuWnd = FindWindowExW(hWnd, NULL, NULL, mainmenu); // start from here

	HWND linear_algebraWnd = FindWindowExW(hWnd, mainmenuWnd, NULL, NULL); // start from here
	
	ShowWindow(linear_algebraWnd, // window handle
		SW_NORMAL); 
	UpdateWindow(linear_algebraWnd);

	HWND system_equationsWnd = FindWindowExW(hWnd, linear_algebraWnd, NULL, NULL);
	ShowWindow(system_equationsWnd, // window handle
		SW_NORMAL); 
	UpdateWindow(system_equationsWnd);

	HWND statsWnd = FindWindowExW(hWnd, system_equationsWnd, NULL, NULL);
	ShowWindow(statsWnd, // window handle
		SW_NORMAL); 
	UpdateWindow(statsWnd);

	HWND logoutWnd = FindWindowExW(hWnd, statsWnd, NULL, NULL);
	
	ShowWindow(logoutWnd, // window handle
		SW_NORMAL); 
	UpdateWindow(logoutWnd);
	UpdateWindow(hWnd);
}

// creates windows needed to display home page.
void CreateMainMenuWnds(HWND hWnd, _In_ int nCmdShow)
{
	// probably bad practice: a blank empty window with a searchable title so when finding windows from the draw function, we can start from this point.
	TCHAR mainmenu[] = _T("mainmenu");
	CreateWindowExW(
		WS_EX_LEFT,
		WC_STATIC,
		mainmenu, 
		WS_CHILD,
		0, 
		0, 
		0,
		0,
		hWnd,
		NULL,
		NULL,
		NULL
	);



	// buttons
	int buttonWidth = 140;
	int buttonHight = 20;
	int linear_algebraEND = 45  + buttonHight + W_SPACING;
	int system_equationsEND = linear_algebraEND + buttonHight + W_SPACING;
	int statsEND = system_equationsEND + buttonHight + W_SPACING;
	int logoutEND = statsEND + buttonHight + W_SPACING;

	// linear algebra
	TCHAR CClinearAlgebra[] = _T("Linear Algebra");
	HWND linear_algebraWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CClinearAlgebra, // text in button
		WS_BORDER | WS_CHILD, // style
		W_CENTER - (buttonWidth / 2), // center
		45, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// system of equations
	TCHAR CCsystemofEquations[] = _T("System of Equations");
	HWND system_equationsWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCsystemofEquations, // text in button
		WS_BORDER | WS_CHILD, // style
		W_CENTER - (buttonWidth / 2), // center
		linear_algebraEND, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// stat
	TCHAR CCstats[] = _T("Stats");
	HWND statsWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCstats, // text in button
		WS_BORDER | WS_CHILD, // style
		W_CENTER - (buttonWidth / 2), // center
		system_equationsEND, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// logout
	TCHAR CClogout[] = _T("Logout");
	HWND logoutWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CClogout, // text in button
		WS_BORDER | WS_CHILD, // style
		W_CENTER - (buttonWidth / 2), // center
		statsEND, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// make window 
	ShowWindow(linear_algebraWnd, // window handle
		nCmdShow);
	UpdateWindow(linear_algebraWnd);

	// make window 
	ShowWindow(system_equationsWnd, // window handle
		nCmdShow);
	UpdateWindow(system_equationsWnd);


	// make window 
	ShowWindow(statsWnd, // window handle
		nCmdShow);
	UpdateWindow(statsWnd);

	// make window 
	ShowWindow(logoutWnd, // window handle
		nCmdShow);
	UpdateWindow(logoutWnd);


	// make window hidden
	ShowWindow(linear_algebraWnd, // window handle
		SW_HIDE);
	UpdateWindow(linear_algebraWnd);

	// make window hidden
	ShowWindow(system_equationsWnd, // window handle
		SW_HIDE);
	UpdateWindow(system_equationsWnd);


	// make window hidden
	ShowWindow(statsWnd, // window handle
		SW_HIDE);
	UpdateWindow(statsWnd);

	// make window hidden
	ShowWindow(logoutWnd, // window handle
		SW_HIDE); 
	UpdateWindow(logoutWnd);
	UpdateWindow(hWnd);
}

// hides main menu windows
void HideMainMenu(_In_ HWND   hWnd)
{
	TCHAR mainmenu[] = _T("mainmenu");
	HWND mainmenuWnd = FindWindowExW(hWnd, NULL, NULL, mainmenu); // start from here

	HWND linear_algebraWnd = FindWindowExW(hWnd, mainmenuWnd, NULL, NULL); 
	
	ShowWindow(linear_algebraWnd, // window handle
		SW_HIDE); 
	UpdateWindow(linear_algebraWnd);

	HWND system_equationsWnd = FindWindowExW(hWnd, linear_algebraWnd, NULL, NULL);
	
	ShowWindow(system_equationsWnd, // window handle
		SW_HIDE); 
	UpdateWindow(system_equationsWnd);

	HWND statsWnd = FindWindowExW(hWnd, system_equationsWnd, NULL, NULL);
	
	ShowWindow(statsWnd, // window handle
		SW_HIDE); 
	UpdateWindow(statsWnd);

	HWND logoutWnd = FindWindowExW(hWnd, statsWnd, NULL, NULL);
	
	ShowWindow(logoutWnd, // window handle
		SW_HIDE); 
	UpdateWindow(logoutWnd);
	UpdateWindow(hWnd);
}
// END: HOMEPAGE

// START: Linear Algebra
// draws the Linear Algebra page when called from WM_PAINT
void DrawLA(HDC hdc, _In_ HWND   hWnd)
{
	TCHAR CCtitle[] = _T("CleverCalc");
	RECT title;
	title.left = 0;
	title.top = 20;
	title.right = W_WIDTH;
	title.bottom = 40; //900x900 is the window size. TODO: make this dynamic. even tho window size wont change from user, this will make it easy if we want to change the default size.
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		CCtitle,// text
		(-1), // text length -1 to find null terminator
		&title, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);


	RECT laSolver;
	laSolver.left = 0;
	laSolver.top = 45;
	laSolver.right = W_WIDTH;
	laSolver.bottom = 65;
	TCHAR text_laSolver[] = _T("Linear Algebra Solver:");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_laSolver,// text
		(-1), // text length -1 to find null terminator
		&laSolver, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);

	

	// display buttons and text fields
	TCHAR la[] = _T("la");
	HWND laWnd = FindWindowExW(hWnd, NULL, NULL, la);

	HWND eqWnd = FindWindowExW(hWnd, laWnd, NULL, NULL);
	ShowWindow(eqWnd, // window handle
		SW_NORMAL);
	UpdateWindow(eqWnd);

	HWND backWnd = FindWindowExW(hWnd, eqWnd, NULL, NULL);
	ShowWindow(backWnd, // window handle
		SW_NORMAL);
	UpdateWindow(backWnd);

	HWND solveWnd = FindWindowExW(hWnd, backWnd, NULL, NULL);\
	ShowWindow(solveWnd, // window handle
		SW_NORMAL);
	UpdateWindow(solveWnd);

	HWND stepWnd = FindWindowExW(hWnd, solveWnd, NULL, NULL);+
	EnableWindow(stepWnd, false);
	ShowWindow(stepWnd, // window handle
		SW_NORMAL);
	UpdateWindow(stepWnd);

	HWND quizWnd = FindWindowExW(hWnd, stepWnd, NULL, NULL);
	EnableWindow(quizWnd, false);
	ShowWindow(quizWnd, // window handle
		SW_NORMAL);
	UpdateWindow(quizWnd);

	HWND genWnd = FindWindowExW(hWnd, quizWnd, NULL, NULL);
	EnableWindow(genWnd, false);
	ShowWindow(genWnd, // window handle
		SW_NORMAL);
	UpdateWindow(genWnd);

	
	// the solWnd will display the solution text.
	HWND solWnd = FindWindowExW(hWnd, genWnd, NULL, NULL);
	ShowWindow(solWnd, // window handle
		SW_NORMAL);
	UpdateWindow(solWnd);
	

	UpdateWindow(hWnd);
}

// creates windows needed to display Linear Algebra page.
void CreateLAWnds(HWND hWnd, _In_ int nCmdShow)
{
	// probably bad practice: a blank empty window with a searchable title so when finding windows from the draw function, we can start from this point.
	TCHAR CCregister[] = _T("la");
	CreateWindowExW(
		WS_EX_LEFT,
		WC_STATIC,
		CCregister,
		WS_CHILD,
		0,
		0,
		0,
		0,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// text box https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexw
	int inputWidth = 650;
	int inputHight = 20;
	static TCHAR CCeq[] = _T("Enter Equation Here.");
	HWND eqWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_EDIT, // EDIT cos its a text box
		CCeq, // text in text box
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (inputWidth / 2)), // center
		70, // TODO: something cleaner
		inputWidth,
		inputHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// buttons
	int buttonWidth = 140;
	int buttonHight = 20;

	static TCHAR CCback[] = _T("Back");
	HWND backWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCback, // text in button
		WS_BORDER | WS_CHILD, // style
		20,
		20, // TODO: something cleaner
		50,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCsolve[] = _T("Quick-Solve");
	HWND solveWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCsolve, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (buttonWidth * 2 + 15)),
		95, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCstep[] = _T("Step-by-Step");
	HWND stepWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCstep, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (buttonWidth + 5)),
		95, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCquiz[] = _T("Quiz Me");
	HWND quizWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCquiz, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER + (buttonWidth  + 15)),
		95, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCgenerate[] = _T("Generate Practice");
	HWND genWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCgenerate, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER + (5)),
		95, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCsolution[] = _T("Solution Window.");
	HWND solWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_STATIC, 
		CCsolution, // text in window
		WS_BORDER | WS_CHILD | SS_CENTER | SS_EDITCONTROL, // style
		(W_CENTER - 325),
		120, // TODO: something cleaner
		650,
		695,
		hWnd,
		NULL,
		NULL,
		NULL
	);




	// TODO: make it so no more copy pasting this command


	
	ShowWindow(eqWnd, // window handle
		nCmdShow);
	UpdateWindow(eqWnd);

	
	ShowWindow(backWnd, // window handle
		nCmdShow);
	UpdateWindow(backWnd);

	
	ShowWindow(solveWnd, // window handle
		nCmdShow);
	UpdateWindow(solveWnd);

	
	ShowWindow(stepWnd, // window handle
		nCmdShow);
	UpdateWindow(stepWnd);

	
	ShowWindow(quizWnd, // window handle
		nCmdShow);
	UpdateWindow(quizWnd);

	
	ShowWindow(genWnd, // window handle
		nCmdShow);
	UpdateWindow(genWnd);

	
	ShowWindow(solWnd, // window handle
		nCmdShow);
	UpdateWindow(solWnd);

	// make window hidden
	ShowWindow(eqWnd, // window handle
		SW_HIDE);
	UpdateWindow(eqWnd);

	ShowWindow(backWnd, // window handle
		SW_HIDE);
	UpdateWindow(backWnd);

	ShowWindow(solveWnd, // window handle
		SW_HIDE);
	UpdateWindow(solveWnd);

	ShowWindow(stepWnd, // window handle
		SW_HIDE);
	UpdateWindow(stepWnd);

	ShowWindow(quizWnd, // window handle
		SW_HIDE);
	UpdateWindow(quizWnd);

	ShowWindow(genWnd, // window handle
		SW_HIDE);
	UpdateWindow(genWnd);

	ShowWindow(solWnd, // window handle
		SW_HIDE);
	UpdateWindow(solWnd);

	UpdateWindow(hWnd);
}

// hides Linear Algebra windows
void HideLA(_In_ HWND   hWnd)
{
	TCHAR la[] = _T("la");
	HWND laWnd = FindWindowExW(hWnd, NULL, NULL, la);

	HWND eqWnd = FindWindowExW(hWnd, laWnd, NULL, NULL);
	SetWindowTextW(eqWnd, clear);
	ShowWindow(eqWnd, // window handle
		SW_HIDE);
	UpdateWindow(eqWnd);

	HWND backWnd = FindWindowExW(hWnd, eqWnd, NULL, NULL);
	ShowWindow(backWnd, // window handle
		SW_HIDE);
	UpdateWindow(backWnd);

	HWND solveWnd = FindWindowExW(hWnd, backWnd, NULL, NULL);
	ShowWindow(solveWnd, // window handle
		SW_HIDE);
	UpdateWindow(solveWnd);

	HWND stepWnd = FindWindowExW(hWnd, solveWnd, NULL, NULL);
	ShowWindow(stepWnd, // window handle
		SW_HIDE);
	UpdateWindow(stepWnd);

	HWND quizWnd = FindWindowExW(hWnd, stepWnd, NULL, NULL);
	ShowWindow(quizWnd, // window handle
		SW_HIDE);
	UpdateWindow(quizWnd);

	HWND genWnd = FindWindowExW(hWnd, quizWnd, NULL, NULL);
	ShowWindow(genWnd, // window handle
		SW_HIDE);
	UpdateWindow(genWnd);

	HWND solWnd = FindWindowExW(hWnd, genWnd, NULL, NULL);
	SetWindowTextW(solWnd, clear);
	ShowWindow(solWnd, // window handle
		SW_HIDE);
	UpdateWindow(solWnd);

	UpdateWindow(hWnd);
}

// updates a solution window using a vector string containing desired update text.
void UpdateSolutionWnd(HWND hWnd, std::vector<std::string> * pInput)
{
	TCHAR finalOutput[TCHAR_MAX];
	int tcharIndex = 0;
	for (int i = 0; i < pInput->size() && tcharIndex < TCHAR_MAX; i++)
	{
		for (int j = 0; j < pInput->at(i).length() && tcharIndex < TCHAR_MAX; j++)
		{
			finalOutput[tcharIndex] = pInput->at(i)[j]; // copy over each character from each line over to a single tchar.
			tcharIndex++;
		}
		finalOutput[tcharIndex] = '\n'; // new line for next input
		tcharIndex++;
	} 

	// insert null terminator
	if (TCHAR_MAX > tcharIndex)
	{
		finalOutput[tcharIndex] = '\0'; // if the input length is less than the TCHAR size, insernt the null terminator at the end of the copied string
	}
	else
	{
		finalOutput[TCHAR_MAX - 1] = '\0'; // if the input was cut off, or filled the entire TCHAR, then insert the terminator at the end of the TCHAR
	}
	SetWindowText(hWnd, finalOutput);
}

// END: Linear Algebra

// START: Systems of Equations
// draws the Systems of Equations page when called from WM_PAINT
void DrawSoE(HDC hdc, _In_ HWND   hWnd)
{
	TCHAR CCtitle[] = _T("CleverCalc");
	RECT title;
	title.left = 0;
	title.top = 20;
	title.right = W_WIDTH;
	title.bottom = 40; //900x900 is the window size. TODO: make this dynamic. even tho window size wont change from user, this will make it easy if we want to change the default size.
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		CCtitle,// text
		(-1), // text length -1 to find null terminator
		&title, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);


	RECT soeSolver;
	soeSolver.left = 0;
	soeSolver.top = 45;
	soeSolver.right = W_WIDTH;
	soeSolver.bottom = 65;
	TCHAR text_soeSolver[] = _T("Systems of Equations Solver. Currently doesn\'t solve systems of equations, see the Linear Algebra solver.");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_soeSolver,// text
		(-1), // text length -1 to find null terminator
		&soeSolver, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);



	// display buttons and text fields
	TCHAR soeq[] = _T("soeq");
	HWND soeWnd = FindWindowExW(hWnd, NULL, NULL, soeq);

	HWND eqWnd = FindWindowExW(hWnd, soeWnd, NULL, NULL);
	ShowWindow(eqWnd, // window handle
		SW_NORMAL);
	UpdateWindow(eqWnd);

	HWND backWnd = FindWindowExW(hWnd, eqWnd, NULL, NULL);
	ShowWindow(backWnd, // window handle
		SW_NORMAL);
	UpdateWindow(backWnd);

	HWND solveWnd = FindWindowExW(hWnd, backWnd, NULL, NULL);
	ShowWindow(solveWnd, // window handle
		SW_NORMAL);
	UpdateWindow(solveWnd);

	HWND stepWnd = FindWindowExW(hWnd, solveWnd, NULL, NULL);
	EnableWindow(stepWnd, false);
	ShowWindow(stepWnd, // window handle
		SW_NORMAL);
	UpdateWindow(stepWnd);

	HWND quizWnd = FindWindowExW(hWnd, stepWnd, NULL, NULL);
	EnableWindow(quizWnd, false);
	ShowWindow(quizWnd, // window handle
		SW_NORMAL);
	UpdateWindow(quizWnd);

	HWND genWnd = FindWindowExW(hWnd, quizWnd, NULL, NULL);
	EnableWindow(genWnd, false);
	ShowWindow(genWnd, // window handle
		SW_NORMAL);
	UpdateWindow(genWnd);

	HWND solWnd = FindWindowExW(hWnd, genWnd, NULL, NULL);
	ShowWindow(solWnd, // window handle
		SW_NORMAL);
	UpdateWindow(solWnd);

	UpdateWindow(hWnd);
}

// creates windows needed to display Systems of Equations page.
void CreateSoEWnds(HWND hWnd, _In_ int nCmdShow)
{
	// probably bad practice: a blank empty window with a searchable title so when finding windows from the draw function, we can start from this point.
	TCHAR CCregister[] = _T("soeq");
	CreateWindowExW(
		WS_EX_LEFT,
		WC_STATIC,
		CCregister,
		WS_CHILD,
		0,
		0,
		0,
		0,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// text box https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowa
	int inputWidth = 650;
	int inputHight = 20;
	static TCHAR CCeq[] = _T("Enter Equations Here, seperated by a semicolon ';'.");
	HWND eqWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_EDIT, // EDIT cos its a text box
		CCeq, // text in text box
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (inputWidth / 2)), // center
		70, // TODO: something cleaner
		inputWidth,
		inputHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	// buttons
	int buttonWidth = 140;
	int buttonHight = 20;

	static TCHAR CCback[] = _T("Back");
	HWND backWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCback, // text in button
		WS_BORDER | WS_CHILD, // style
		20,
		20, // TODO: something cleaner
		50,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCsolve[] = _T("Quick-Solve");
	HWND solveWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCsolve, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (buttonWidth * 2 + 15)),
		95, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCstep[] = _T("Step-by-Step");
	HWND stepWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCstep, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (buttonWidth + 5)),
		95, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCquiz[] = _T("Quiz Me");
	HWND quizWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCquiz, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER + (buttonWidth + 15)),
		95, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCgenerate[] = _T("Generate Practice");
	HWND genWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCgenerate, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER + (5)),
		95, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCsolution[] = _T("Solution Window.");
	HWND solWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_STATIC,
		CCsolution, // text in button
		WS_BORDER | WS_CHILD | SS_CENTER, // style
		(W_CENTER - 325),
		120, // TODO: something cleaner
		650,
		695,
		hWnd,
		NULL,
		NULL,
		NULL
	);




	// TODO: make it so no more copy pasting this command


	
	ShowWindow(eqWnd, // window handle
		nCmdShow);
	UpdateWindow(eqWnd);

	
	ShowWindow(backWnd, // window handle
		nCmdShow);
	UpdateWindow(backWnd);

	
	ShowWindow(solveWnd, // window handle
		nCmdShow);
	UpdateWindow(solveWnd);

	
	ShowWindow(stepWnd, // window handle
		nCmdShow);
	UpdateWindow(stepWnd);

	
	ShowWindow(quizWnd, // window handle
		nCmdShow);
	UpdateWindow(quizWnd);

	
	ShowWindow(genWnd, // window handle
		nCmdShow);
	UpdateWindow(genWnd);

	
	ShowWindow(solWnd, // window handle
		nCmdShow);
	UpdateWindow(solWnd);

	// make window hidden
	ShowWindow(eqWnd, // window handle
		SW_HIDE);
	UpdateWindow(eqWnd);

	ShowWindow(backWnd, // window handle
		SW_HIDE);
	UpdateWindow(backWnd);

	ShowWindow(solveWnd, // window handle
		SW_HIDE);
	UpdateWindow(solveWnd);

	ShowWindow(stepWnd, // window handle
		SW_HIDE);
	UpdateWindow(stepWnd);

	ShowWindow(quizWnd, // window handle
		SW_HIDE);
	UpdateWindow(quizWnd);

	ShowWindow(genWnd, // window handle
		SW_HIDE);
	UpdateWindow(genWnd);

	ShowWindow(solWnd, // window handle
		SW_HIDE);
	UpdateWindow(solWnd);

	UpdateWindow(hWnd);
}

// hides stats windows
void HideSoE(_In_ HWND   hWnd)
{
	TCHAR soeq[] = _T("soeq");
	HWND soeWnd = FindWindowExW(hWnd, NULL, NULL, soeq);

	HWND eqWnd = FindWindowExW(hWnd, soeWnd, NULL, NULL);
	SetWindowTextW(eqWnd, clear);
	ShowWindow(eqWnd, // window handle
		SW_HIDE);
	UpdateWindow(eqWnd);

	HWND backWnd = FindWindowExW(hWnd, eqWnd, NULL, NULL);
	ShowWindow(backWnd, // window handle
		SW_HIDE);
	UpdateWindow(backWnd);

	HWND solveWnd = FindWindowExW(hWnd, backWnd, NULL, NULL);
	ShowWindow(solveWnd, // window handle
		SW_HIDE);
	UpdateWindow(solveWnd);

	HWND stepWnd = FindWindowExW(hWnd, solveWnd, NULL, NULL);
	ShowWindow(stepWnd, // window handle
		SW_HIDE);
	UpdateWindow(stepWnd);

	HWND quizWnd = FindWindowExW(hWnd, stepWnd, NULL, NULL);
	ShowWindow(quizWnd, // window handle
		SW_HIDE);
	UpdateWindow(quizWnd);

	HWND genWnd = FindWindowExW(hWnd, quizWnd, NULL, NULL);
	ShowWindow(genWnd, // window handle
		SW_HIDE);
	UpdateWindow(genWnd);

	HWND solWnd = FindWindowExW(hWnd, genWnd, NULL, NULL);
	SetWindowTextW(solWnd, clear);
	ShowWindow(solWnd, // window handle
		SW_HIDE);
	UpdateWindow(solWnd);

	UpdateWindow(hWnd);
}
// END: Linear Algebra

// START: stats
// draws the Systems of Equations page when called from WM_PAINT
void DrawStats(HDC hdc, _In_ HWND   hWnd)
{
	TCHAR CCtitle[] = _T("CleverCalc");
	RECT title;
	title.left = 0;
	title.top = 20;
	title.right = W_WIDTH;
	title.bottom = 40; //900x900 is the window size. TODO: make this dynamic. even tho window size wont change from user, this will make it easy if we want to change the default size.
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		CCtitle,// text
		(-1), // text length -1 to find null terminator
		&title, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);


	RECT soeSolver;
	soeSolver.left = 0;
	soeSolver.top = 45;
	soeSolver.right = W_WIDTH;
	soeSolver.bottom = 65;
	TCHAR text_soeSolver[] = _T("Quiz Stats:");
	DrawTextExW( //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtextexw
		hdc, // handle
		text_soeSolver,// text
		(-1), // text length -1 to find null terminator
		&soeSolver, // refrence rect to contain text
		DT_CENTER | DT_TOP, // parameters
		NULL // extra params
	);



	// display buttons and text fields
	TCHAR stats[] = _T("statistics"); 
	HWND sWnd = FindWindowExW(hWnd, NULL, NULL, stats);

	HWND backWnd = FindWindowExW(hWnd, sWnd, NULL, NULL);

	ShowWindow(backWnd, // window handle
		SW_NORMAL);
	UpdateWindow(backWnd);

	HWND statsWnd = FindWindowExW(hWnd, backWnd, NULL, NULL);

	ShowWindow(statsWnd, // window handle
		SW_NORMAL);
	UpdateWindow(statsWnd);

	HWND weekWnd = FindWindowExW(hWnd, statsWnd, NULL, NULL);

	ShowWindow(weekWnd, // window handle
		SW_NORMAL);
	UpdateWindow(weekWnd);

	HWND oneMonthWnd = FindWindowExW(hWnd, weekWnd, NULL, NULL);

	ShowWindow(oneMonthWnd, // window handle
		SW_NORMAL);
	UpdateWindow(oneMonthWnd);

	HWND threeMonthWnd = FindWindowExW(hWnd, oneMonthWnd, NULL, NULL);

	ShowWindow(threeMonthWnd, // window handle
		SW_NORMAL);
	UpdateWindow(threeMonthWnd);

	HWND sixMonthWnd = FindWindowExW(hWnd, threeMonthWnd, NULL, NULL);

	ShowWindow(sixMonthWnd, // window handle
		SW_NORMAL);
	UpdateWindow(sixMonthWnd);

	UpdateWindow(hWnd);
}

// creates windows needed to display stats page.
void CreateStatsWbds(HWND hWnd, _In_ int nCmdShow)
{
	// probably bad practice: a blank empty window with a searchable title so when finding windows from the draw function, we can start from this point.
	TCHAR CCs[] = _T("statistics"); // each of these is based of the length, not contents of the string, due to how FindWindowExW works. idk why.
	CreateWindowExW(
		WS_EX_LEFT,
		WC_STATIC,
		CCs,
		WS_CHILD,
		0,
		0,
		0,
		0,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	

	// buttons
	int buttonWidth = 140;
	int buttonHight = 20;

	static TCHAR CCback[] = _T("Back");
	HWND backWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCback, // text in button
		WS_BORDER | WS_CHILD, // style
		20,
		20, // TODO: something cleaner
		50,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCstats[] = _T("Future Graph Window.");
	HWND statsWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_STATIC,
		CCstats, // text in button
		WS_BORDER | WS_CHILD |  SS_CENTER, // style
		(W_CENTER - 325),
		90, // TODO: something cleaner
		650,
		600,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCweek[] = _T("1 Week");
	HWND weekWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCweek, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (buttonWidth*2 + 15)),
		715, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CConeMonth[] = _T("1 Month");
	HWND oneMonthWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CConeMonth, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER - (buttonWidth + 5)),
		715, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCthreeMonth[] = _T("3 Months");
	HWND threeMonthWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCthreeMonth, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER + 5 ),
		715, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	static TCHAR CCsixMonth[] = _T("6 Months");
	HWND sixMonthWnd = CreateWindowExW(
		WS_EX_LEFT,
		WC_BUTTON, // button
		CCsixMonth, // text in button
		WS_BORDER | WS_CHILD, // style
		(W_CENTER + buttonWidth + 15),
		715, // TODO: something cleaner
		buttonWidth,
		buttonHight,
		hWnd,
		NULL,
		NULL,
		NULL
	);



	// TODO: make it so no more copy pasting this command


	
	ShowWindow(backWnd, // window handle
		nCmdShow);
	UpdateWindow(backWnd);

	
	ShowWindow(statsWnd, // window handle
		nCmdShow);
	UpdateWindow(statsWnd);

	
	ShowWindow(weekWnd, // window handle
		nCmdShow);
	UpdateWindow(weekWnd);

	
	ShowWindow(oneMonthWnd, // window handle
		nCmdShow);
	UpdateWindow(oneMonthWnd);

	
	ShowWindow(threeMonthWnd, // window handle
		nCmdShow);
	UpdateWindow(threeMonthWnd);

	
	ShowWindow(sixMonthWnd, // window handle
		nCmdShow);
	UpdateWindow(sixMonthWnd);

	
	ShowWindow(backWnd, // window handle
		SW_HIDE);
	UpdateWindow(backWnd);

	
	ShowWindow(statsWnd, // window handle
		SW_HIDE);
	UpdateWindow(statsWnd);

	
	ShowWindow(weekWnd, // window handle
		SW_HIDE);
	UpdateWindow(weekWnd);

	
	ShowWindow(oneMonthWnd, // window handle
		SW_HIDE);
	UpdateWindow(oneMonthWnd);

	
	ShowWindow(threeMonthWnd, // window handle
		SW_HIDE);
	UpdateWindow(threeMonthWnd);

	
	ShowWindow(sixMonthWnd, // window handle
		SW_HIDE);
	UpdateWindow(sixMonthWnd);

	UpdateWindow(hWnd);
}

// hides stats windows
void HideStats(_In_ HWND   hWnd)
{
	TCHAR stats[] = _T("statistics");
	HWND sWnd = FindWindowExW(hWnd, NULL, NULL, stats);

	HWND backWnd = FindWindowExW(hWnd, sWnd, NULL, NULL);
	
	ShowWindow(backWnd, // window handle
		SW_HIDE);
	UpdateWindow(backWnd);

	HWND statsWnd = FindWindowExW(hWnd, backWnd, NULL, NULL);
	
	ShowWindow(statsWnd, // window handle
		SW_HIDE);
	UpdateWindow(statsWnd);

	HWND weekWnd = FindWindowExW(hWnd, statsWnd, NULL, NULL);
	
	ShowWindow(weekWnd, // window handle
		SW_HIDE);
	UpdateWindow(weekWnd);

	HWND oneMonthWnd = FindWindowExW(hWnd, weekWnd, NULL, NULL);
	
	ShowWindow(oneMonthWnd, // window handle
		SW_HIDE);
	UpdateWindow(oneMonthWnd);

	HWND threeMonthWnd = FindWindowExW(hWnd, oneMonthWnd, NULL, NULL);
	
	ShowWindow(threeMonthWnd, // window handle
		SW_HIDE);
	UpdateWindow(threeMonthWnd);

	HWND sixMonthWnd = FindWindowExW(hWnd, threeMonthWnd, NULL, NULL);
	
	ShowWindow(sixMonthWnd, // window handle
		SW_HIDE);
	UpdateWindow(sixMonthWnd);

	UpdateWindow(hWnd);
}
// END: stats

// checks string for containing only valid characters. {numbers, x, y, =, +, -, /, *, (, )}
bool ValidInput(const std::string* pInput, bool multitpleEQs = false)
{
	bool valid = true, wasXFound = false, wasYFound = false, wasEqFound = false; // TODO something more encompassing. 
	int validCharSize = 20;
	const char validChars[] = { ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'x', 'x', '=', '+', '-', '/', '*', '(', ')', ';'}; // there are two x's. this is because using y is currently not allowed.
	if (multitpleEQs) validCharSize = 21;
	for (int i = 0; i < pInput->size(); i++)
	{
		bool inTheList = false;
		for (int j = 0; j < validCharSize; j++)
		{
			if (pInput->at(i) == validChars[j])
			{
				if (validChars[j] == 'x') wasXFound = true;
				else if (validChars[j] == 'y') wasYFound = true;
				else if (validChars[j] == '=') wasEqFound = true;
				inTheList = true;
				break;
			}
		}
		if (inTheList == false)
		{
			valid = false;
			break;
		}
	}
	if (wasXFound == false || wasEqFound == false) valid = false; // TODO yes it needs to actually check function integrety.
	return valid;
}

void UserGivePoint(int *inputID)
{
	TCHAR tcentry[64];
	int points = 0, userID;
	std::ifstream userlistIn;
	std::ofstream userlistOut;
	userlistIn.open(UL, std::ios::in);
	std::string temp, replaceme;

	if(userlistIn.is_open())
	{
		// to start we need to seach previous entries to find the correct user id
		if (userlistIn.beg != userlistIn.end)
		{
			userlistIn.seekg(0, userlistIn.beg);
			for (int i = 0; i < 500; i++) // prevent infinite looping
			{
				if (userlistIn.cur == userlistIn.beg || userlistIn.peek() == '{')
				{
					userlistIn.seekg(1, userlistIn.cur);
					while (userlistIn.peek() != ';')
					{
						temp.push_back(userlistIn.peek());
						userlistIn.seekg(1, userlistIn.cur);
					}
					userID = stoi(temp); // assign current userid
					if (userID == *inputID)
					{
						while (userlistIn.peek() != '}') // nav to end line
						{
							userlistIn.seekg(1, userlistIn.cur);
						}
						userlistIn.seekg(-2, userlistIn.cur);
						while (userlistIn.peek() != ';') // nav to start of points
						{
							userlistIn.seekg(-1, userlistIn.cur);
						}
						userlistIn.seekg(1, userlistIn.cur);
						temp.clear();
						while (userlistIn.peek() != ';') // nav to end of points and store value
						{
							temp.push_back(userlistIn.peek());
							userlistIn.seekg(1, userlistIn.cur);
						}
					}
					break;
				}
			}
		}
		
		points = stoi(temp);
		points++; // points incremented
		userlistIn.seekg(0, userlistIn.beg);
		temp.clear();
		
		userlistIn.peek();
		while (userlistIn.eof() == false)
		{
			temp.push_back(userlistIn.get());
			userlistIn.peek();
		}
		replaceme = std::to_string((points-1));
		temp.replace(temp.find(replaceme), replaceme.length(), std::to_string(points));

		userlistIn.close();		
	}
	

	userlistOut.open(UL, std::ios::out);
	if (userlistOut)
	{
		userlistOut << temp;
		userlistOut.close();
	}
}

// window-procedure function
// handles event messages from windows
// use this function to deal with user interation
LRESULT CALLBACK WndProc(
	_In_ HWND   hWnd,
	_In_ UINT   message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	// fetch application state: https://learn.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-/
	StateInfo* state; 
	if (message == WM_CREATE) // for the first time
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		state = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)state); // stores pointer for user later
	}
	else // every other time
	{
		LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
		state = reinterpret_cast<StateInfo*>(ptr);
	}


	TCHAR tcentry[64];
	// painting the window
	PAINTSTRUCT ps; 
	HDC hdc; 
	
	switch (message)
	{
	case WM_PAINT: // windows told us to paint ||| help with wm_paint (winuser.h): https://learn.microsoft.com/en-us/windows/win32/api/_gdi/
		hdc = BeginPaint(hWnd, &ps); 

		//draws different pages depending on which part of the application the user is in.
		switch (state->currentPage)
		{
		case state->home:
			DrawHomePage(hdc, hWnd);
			break;
		case state->createAcc:
			DrawRegister(hdc, hWnd);
			break;
		case state->forgotPass:
			DrawForgot(hdc, hWnd);
			break;
		case state->mainMenu:
			DrawMainMenu(hdc, hWnd);
			break;
		case state->linAlgebra:
			DrawLA(hdc, hWnd);
			break;
		case state->sysEquations:
			DrawSoE(hdc, hWnd);
			break;
		case state->stats:
			DrawStats(hdc, hWnd);
			break;
		}		
		
		EndPaint(hWnd, &ps);
		break;

	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			switch (state->currentPage)
			{

			case state->home:
				// figure out which button was pressed then change the state of the program and or do something else. more logic can be added to each if statement as needed
			{
				HWND button = reinterpret_cast<HWND>(lParam);
				HWND usernameWnd = FindWindowExW(hWnd, NULL, NULL, NULL);
				HWND passwordWnd = FindWindowExW(hWnd, usernameWnd, NULL, NULL);
				HWND forgotWnd = FindWindowExW(hWnd, passwordWnd, NULL, NULL);
				HWND loginWnd = FindWindowExW(hWnd, forgotWnd, NULL, NULL);
				HWND registerWnd = FindWindowExW(hWnd, loginWnd, NULL, NULL);
				if (button == forgotWnd)
				{
					state->currentPage = state->forgotPass;
					HideHomePage(hWnd);
					InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
				}
				else if (button == loginWnd) // if login button was clicked, change state to main menu.
				{
					std::string entry = "", sum = "", temp = "";
					int userID = 0;
					bool usernameFound = false, passwordMatch = false;
					std::ifstream userlistIn;
					userlistIn.open(UL, std::ios::in);
					if (userlistIn.is_open())
					{
						if (userlistIn.beg != userlistIn.end)
						{
							// check for similar username
							temp.clear();
							GetWindowTextW(usernameWnd, tcentry, 64);
							TCHAR2String(tcentry, 64, &entry);
							userlistIn.seekg(0, userlistIn.beg); // goto begining of file
							for (int i = 0; i < 1000; i++) // prevent infinite looping
							{
								if (userlistIn.peek() == '{')
								{
									userlistIn.seekg(1, userlistIn.cur);
									while (userlistIn.peek() != ';')
									{
										userlistIn.seekg(1, userlistIn.cur);
									} // advanced to next part of entry
									userlistIn.seekg(1, userlistIn.cur);
									while (userlistIn.peek() != ';')
									{
										temp.push_back(userlistIn.peek());
										userlistIn.seekg(1, userlistIn.cur);
									}
									if (entry.compare(temp) == 0)
									{
										usernameFound = true;
										// now check password
										temp.clear();
										entry.clear();
										GetWindowTextW(passwordWnd, tcentry, 64);
										TCHAR2String(tcentry, 64, &entry);

										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';')
										{
											userlistIn.seekg(1, userlistIn.cur);
										} // advanced to next part of entry
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';')
										{
											temp.push_back(userlistIn.peek());
											userlistIn.seekg(1, userlistIn.cur);
										}
										if (entry.compare(temp) == 0)
										{
											passwordMatch = true;
										}
										break;
									}
									temp.clear();
								}
								if (userlistIn.peek() == '}') userlistIn.seekg(3, userlistIn.cur); // important or you cannot pass the newline character
								else userlistIn.seekg(1, userlistIn.cur);
								if (userlistIn.eof()) break;
							}
							entry.clear();

							if (usernameFound && passwordMatch)
							{
								temp.clear();
								// last we need to seach back to find user ID
								for (int i = 0; i < 500; i++) // prevent infinite looping
								{
									if (userlistIn.cur != userlistIn.beg) userlistIn.seekg(-1, userlistIn.cur);
									if (userlistIn.cur == userlistIn.beg || userlistIn.peek() == '{')
									{
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';')
										{
											temp.push_back(userlistIn.peek());
											userlistIn.seekg(1, userlistIn.cur);
										}
										userID = stoi(temp); // assign current userid
										break;
									}
								}

							}
						}
							userlistIn.close();
					}

					if (usernameFound && passwordMatch)
					{
						state->currentUser = userID;
						state->currentPage = state->mainMenu;
						HideHomePage(hWnd); // in this case, a state change occured so the homepage windows will be removed.
						InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
					}
					else MessageBox(hWnd, L"Username/Password combination not found.", L"CleverCalc", MB_OK);
					
				} 
				else if (button == registerWnd)
				{
					state->currentPage = state->createAcc;
					HideHomePage(hWnd);
					InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
				}
			}
				break;
			case state->createAcc:
			{
				HWND button = reinterpret_cast<HWND>(lParam);
				TCHAR CCregister[] = _T("reg");
				HWND regWnd = FindWindowExW(hWnd, NULL, NULL, CCregister);
				HWND emailWnd = FindWindowExW(hWnd, regWnd, NULL, NULL);
				HWND usernameWnd = FindWindowExW(hWnd, emailWnd, NULL, NULL);
				HWND passwordWnd = FindWindowExW(hWnd, usernameWnd, NULL, NULL);
				HWND password2Wnd = FindWindowExW(hWnd, passwordWnd, NULL, NULL);
				HWND registerWnd = FindWindowExW(hWnd, password2Wnd, NULL, NULL);
				if (button == registerWnd)
				{
					std::string entry = "", sum = "", temp = "";
					int userID = 1;
					bool usernameTaken = false, emailTaken = false, passwordMatch = false, badchar = false;
					
					GetWindowTextW(emailWnd, tcentry, 64);
					TCHAR2String(tcentry, 64, &entry);
					if (entry.find(';') != std::string::npos || entry.find('{') != std::string::npos || entry.find('}') != std::string::npos) badchar = true;
					entry.clear();
					GetWindowTextW(usernameWnd, tcentry, 64);
					TCHAR2String(tcentry, 64, &entry);
					if (entry.find(';') != std::string::npos || entry.find('{') != std::string::npos || entry.find('}') != std::string::npos) badchar = true;
					entry.clear();
					GetWindowTextW(passwordWnd, tcentry, 64);
					TCHAR2String(tcentry, 64, &entry);
					if (entry.find(';') != std::string::npos || entry.find('{') != std::string::npos || entry.find('}') != std::string::npos) badchar = true;
					entry.clear();

					if (badchar)
					{
						MessageBox(hWnd, L"Invalid input characters ({, }, ;).", L"CleverCalc", MB_OK);
					}
					else
					{
						std::ifstream userlistIn;
						std::ofstream userlistOut;
						userlistIn.open(UL, std::ios::in);
						if (userlistIn.is_open())
						{
							// to start we need to seach previous entries to find the last user id
							if (userlistIn.beg != userlistIn.end)
							{
								userlistIn.seekg(0, userlistIn.end);
								for (int i = 0; i < 500; i++) // prevent infinite looping
								{
									if (userlistIn.cur != userlistIn.beg) userlistIn.seekg(-1, userlistIn.cur);
									if (userlistIn.cur == userlistIn.beg || userlistIn.peek() == '{')
									{
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';')
										{
											temp.push_back(userlistIn.peek());
											userlistIn.seekg(1, userlistIn.cur);
										}
										userID = stoi(temp); // assign current userid
										userID++; // advanced to next one
										break;
									}
								}

								// check for similar username
								temp.clear();
								GetWindowTextW(usernameWnd, tcentry, 64);
								TCHAR2String(tcentry, 64, &entry);
								userlistIn.seekg(0, userlistIn.beg); // goto begining of file
								for (int i = 0; i < 1000; i++) // prevent infinite looping
								{
									if (userlistIn.peek() == '{')
									{
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';')
										{
											userlistIn.seekg(1, userlistIn.cur);
										} // advanced to next part of entry
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';')
										{
											temp.push_back(userlistIn.peek());
											userlistIn.seekg(1, userlistIn.cur);
										}
										if (entry.compare(temp) == 0)
										{
											usernameTaken = true;
											break;
										}
										temp.clear();
									}

									userlistIn.seekg(1, userlistIn.cur);
									if (userlistIn.eof()) break;
								}
								entry.clear();


								// check for similar email
								temp.clear();
								GetWindowTextW(emailWnd, tcentry, 64);
								TCHAR2String(tcentry, 64, &entry);
								userlistIn.seekg(0, userlistIn.beg); // goto begining of file
								for (int i = 0; i < 1000; i++) // prevent infinite looping
								{
									if (userlistIn.peek() == '{')
									{
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';')
										{
											userlistIn.seekg(1, userlistIn.cur);
										} // advanced to next part of entry
										while (userlistIn.peek() != ';')
										{
											userlistIn.seekg(1, userlistIn.cur);
										} // advanced to next part of entry
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';')
										{
											temp.push_back(userlistIn.peek());
											userlistIn.seekg(1, userlistIn.cur);
										}
										if (entry.compare(temp) == 0)
										{
											emailTaken = true;
											break;
										}
										temp.clear();
									}

									userlistIn.seekg(1, userlistIn.cur);
									if (userlistIn.eof()) break;
								}
								entry.clear();
							}
							userlistIn.close();
						}

						// passwords check
						entry.clear();
						temp.clear();
						GetWindowTextW(passwordWnd, tcentry, 64);
						TCHAR2String(tcentry, 64, &entry);
						GetWindowTextW(password2Wnd, tcentry, 64);
						TCHAR2String(tcentry, 64, &temp);
						if (entry.compare(temp) == 0) passwordMatch = true;


						if (usernameTaken)
						{
							MessageBox(hWnd, L"Username Taken.", L"CleverCalc", MB_OK);
						}
						else if (emailTaken)
						{
							MessageBox(hWnd, L"Email Taken.", L"CleverCalc", MB_OK);
						}
						else if (passwordMatch == false)
						{
							MessageBox(hWnd, L"Passwords don\'t match.", L"CleverCalc", MB_OK);
						}
						else
						{
							userlistOut.open(UL, std::ios::out | std::ios::app);
						}

						if (userlistOut.is_open())
						{
							userlistOut.seekp(userlistOut.end);
							entry.clear();
							// okay now we need to add the new entry
							sum.push_back('{'); // start of entry

							sum.append(std::to_string(userID)); // user id
							sum.push_back(';'); // end of user id

							GetWindowTextW(usernameWnd, tcentry, 64);
							TCHAR2String(tcentry, 64, &entry);
							sum.append(entry); // username
							entry.clear();
							sum.push_back(';'); // end of user name

							GetWindowTextW(emailWnd, tcentry, 64);
							TCHAR2String(tcentry, 64, &entry);
							sum.append(entry); // email
							entry.clear();
							sum.push_back(';'); // end of email

							GetWindowTextW(passwordWnd, tcentry, 64);
							TCHAR2String(tcentry, 64, &entry);
							sum.append(entry); // password
							entry.clear();
							sum.push_back(';'); // end of password

							// number of calculation preformed (or possibly some other value in the future)
							sum.push_back('0');
							sum.push_back(';');

							sum.push_back('}'); // end of entry
							sum.push_back('\n'); // end of entry

							userlistOut << sum;
							userlistOut.close();

							//TCHARClear(tcentry, 64); // clear input windows
							//SetWindowTextW(usernameWnd, tcentry);
							//SetWindowTextW(emailWnd, tcentry);
							//SetWindowTextW(passwordWnd, tcentry);
							//SetWindowTextW(password2Wnd, tcentry);
							state->currentPage = state->home;
							HideRegister(hWnd);
							InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
						}
					}

					
				}
			}
				break;
			case state->forgotPass:
			{
				HWND button = reinterpret_cast<HWND>(lParam);
				TCHAR forgot[] = _T("forgot");
				HWND forgotWnd = FindWindowExW(hWnd, NULL, NULL, forgot);
				HWND usernameWnd = FindWindowExW(hWnd, forgotWnd, NULL, NULL);
				HWND emailWnd = FindWindowExW(hWnd, usernameWnd, NULL, NULL);
				HWND passWnd = FindWindowExW(hWnd, emailWnd, NULL, NULL);
				HWND recoverWnd = FindWindowExW(hWnd, passWnd, NULL, NULL);

				if (button == recoverWnd)
				{
					std::string entry = "", sum = "", temp = "", replaceme = "";
					int currentScore = 0;
					bool usernameFound = false, emailMatch = false;
					std::ifstream userlistIn;
					std::ofstream userlistOut;

					GetWindowTextW(passWnd, tcentry, 64);
					TCHAR2String(tcentry, 64, &entry);
					if (entry.find(';') == std::string::npos && entry.find('{') == std::string::npos && entry.find('}') == std::string::npos)
					{
						entry.clear();
						userlistIn.open(UL, std::ios::in);
						if (userlistIn.is_open())
						{
							if (userlistIn.beg != userlistIn.end)
							{
								// check for similar username
								temp.clear();
								GetWindowTextW(usernameWnd, tcentry, 64);
								TCHAR2String(tcentry, 64, &entry);
								userlistIn.seekg(0, userlistIn.beg); // goto begining of file
								for (int i = 0; i < 1000; i++) // prevent infinite looping
								{
									if (userlistIn.peek() == '{')
									{
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';')
										{
											userlistIn.seekg(1, userlistIn.cur);
										} // advanced to next part of entry
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';')
										{
											temp.push_back(userlistIn.peek());
											userlistIn.seekg(1, userlistIn.cur);
										}
										if (entry.compare(temp) == 0)
										{
											usernameFound = true;
											// now check email
											temp.clear();
											entry.clear();
											GetWindowTextW(emailWnd, tcentry, 64);
											TCHAR2String(tcentry, 64, &entry);
											userlistIn.seekg(1, userlistIn.cur);
											while (userlistIn.peek() != ';')
											{
												temp.push_back(userlistIn.peek());
												userlistIn.seekg(1, userlistIn.cur);
											}
											if (entry.compare(temp) == 0)
											{
												emailMatch = true;
												userlistIn.seekg(1, userlistIn.cur);
												while (userlistIn.peek() != ';')
												{
													replaceme.push_back(userlistIn.peek());
													userlistIn.seekg(1, userlistIn.cur);
												}

											}
											break;
										}
										temp.clear();
									}
									if (userlistIn.peek() == '}') userlistIn.seekg(3, userlistIn.cur); // important or you cannot pass the newline character
									else userlistIn.seekg(1, userlistIn.cur);
									if (userlistIn.eof()) break;
								}
								entry.clear();
							}
							userlistIn.close();
						}

						if (usernameFound && emailMatch)
						{
							userlistIn.open(UL, std::ios::in);
							entry.clear();
							temp.clear();
							GetWindowTextW(passWnd, tcentry, 64);
							TCHAR2String(tcentry, 64, &entry);



							userlistIn.peek();
							while (userlistIn.eof() == false)
							{
								temp.push_back(userlistIn.get());
								userlistIn.peek();
							}
							temp.replace(temp.find(replaceme), replaceme.length(), entry);

							userlistIn.close();
							userlistOut.open(UL, std::ios::out);
							userlistOut << temp;
							userlistOut.close();
							state->currentPage = state->home;
							HideForgot(hWnd);
							InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
						}
						else MessageBox(hWnd, L"Username/Email combination not found.", L"CleverCalc", MB_OK);
					}
					else 
					{
						MessageBox(hWnd, L"Invalid password characters ({, }, ;).", L"CleverCalc", MB_OK);
					};
					

					
				}
				
			}
				break;
			case state->mainMenu:
			{
				HWND button = reinterpret_cast<HWND>(lParam);
				TCHAR mainmenu[] = _T("mainmenu");
				HWND mainmenuWnd = FindWindowExW(hWnd, NULL, NULL, mainmenu); // start from here
				HWND linear_algebraWnd = FindWindowExW(hWnd, mainmenuWnd, NULL, NULL);
				HWND system_equationsWnd = FindWindowExW(hWnd, linear_algebraWnd, NULL, NULL);
				HWND statsWnd = FindWindowExW(hWnd, system_equationsWnd, NULL, NULL);
				HWND logoutWnd = FindWindowExW(hWnd, statsWnd, NULL, NULL);
				if (button == linear_algebraWnd)
				{
					state->currentPage = state->linAlgebra;
					HideMainMenu(hWnd);
					InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
				}
				else if (button == system_equationsWnd)
				{
					state->currentPage = state->sysEquations;
					HideMainMenu(hWnd);
					InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
				}
				else if (button == statsWnd)
				{
					state->currentPage = state->stats;
					HideMainMenu(hWnd);
					InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
				}
				else if (button == logoutWnd)
				{
					state->currentUser = 0;
					state->currentPage = state->home;
					HideMainMenu(hWnd);
					InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
				}

			}
				break;
			case state->linAlgebra:
			{
				HWND button = reinterpret_cast<HWND>(lParam);
				TCHAR la[] = _T("la");
				HWND laWnd = FindWindowExW(hWnd, NULL, NULL, la);
				HWND eqWnd = FindWindowExW(hWnd, laWnd, NULL, NULL);
				HWND backWnd = FindWindowExW(hWnd, eqWnd, NULL, NULL);
				HWND solveWnd = FindWindowExW(hWnd, backWnd, NULL, NULL);
				HWND stepWnd = FindWindowExW(hWnd, solveWnd, NULL, NULL);
				HWND quizWnd = FindWindowExW(hWnd, stepWnd, NULL, NULL);
				HWND genWnd = FindWindowExW(hWnd, quizWnd, NULL, NULL);
				HWND solWnd = FindWindowExW(hWnd, genWnd, NULL, NULL);

				if (button == backWnd)
				{
					state->currentPage = state->mainMenu;
					state->currentProblem.clear(); // clears the current problem from the program state
					std::vector<std::string> clean = { "Solution Window." };
					UpdateSolutionWnd(solWnd, &clean);
					HideLA(hWnd);
					InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
				}
				else if (button == solveWnd)
				{
					TCHAR solTCHAR[TCHAR_SMALL];
					GetWindowTextW(eqWnd, solTCHAR, TCHAR_SMALL);
					state->currentProblem.clear();
					state->currentProblem.push_back("");
					std::string input = "";
					TCHAR2String(solTCHAR, TCHAR_SMALL, &input);
					if (ValidInput(&input))
					{
						state->currentProblem[0] = input;
						bool solved = false;
						while (!solved)
						{
							try
							{
								laStep(&state->currentProblem);
								UserGivePoint(&(state->currentUser));
							}
							catch (const std::exception& e)
							{
								MessageBox(hWnd, L"Unfortunatly, your equation caused an error. This program is in beta, please be gentle.", L"CleverCalc", MB_OK);
							}
							break; // used until laStep gets a full implementation.
						}
						UpdateSolutionWnd(solWnd, &state->currentProblem);
					}
					else
					{
						MessageBox(hWnd, L"Invalid equation(s). Make sure to only include variables x, +, -, x, /, numbers, and an equal sign. Curretnly doesn\'t solve every equation.", L"CleverCalc", MB_OK);
					}
					
				}
				else if (button == stepWnd)
				{
					TCHAR solTCHAR[TCHAR_SMALL];
					std::string input = "";
					GetWindowTextW(eqWnd, solTCHAR, TCHAR_SMALL);
					TCHAR2String(solTCHAR, TCHAR_SMALL, &input);
					if (ValidInput(&input))
					{
						if (state->currentProblem.size() == 0)
						{
							state->currentProblem.push_back(input); // if there is no equation, fill the current problem
						}
						else if (input.compare(state->currentProblem[0]) != 0)
						{
							state->currentProblem.clear();
							state->currentProblem.push_back(input);
						} // if the equation changed, clear the current problem		
						try
						{
							laStep(&state->currentProblem);
							UserGivePoint(&(state->currentUser));
						}
						catch (const std::exception& e)
						{
							MessageBox(hWnd, L"Unfortunatly, your equation caused an error. This program is in beta, please be gentle.", L"CleverCalc", MB_OK);
						}
						UpdateSolutionWnd(solWnd, &state->currentProblem);
					} 
					else
					{
						MessageBox(hWnd, L"Invalid equation(s). Make sure to only include variables x, +, -, numbers, and an equal sign. Curretnly doesn\'t solve every equation.", L"CleverCalc", MB_OK);
					}
					
				}
			}
				break;
			case state->sysEquations:
			{
				HWND button = reinterpret_cast<HWND>(lParam);
				TCHAR soeq[] = _T("soeq");
				HWND soeWnd = FindWindowExW(hWnd, NULL, NULL, soeq);
				HWND eqWnd = FindWindowExW(hWnd, soeWnd, NULL, NULL);
				HWND backWnd = FindWindowExW(hWnd, eqWnd, NULL, NULL);
				HWND solveWnd = FindWindowExW(hWnd, backWnd, NULL, NULL);
				HWND stepWnd = FindWindowExW(hWnd, solveWnd, NULL, NULL);
				HWND quizWnd = FindWindowExW(hWnd, stepWnd, NULL, NULL);
				HWND genWnd = FindWindowExW(hWnd, quizWnd, NULL, NULL);
				HWND solWnd = FindWindowExW(hWnd, genWnd, NULL, NULL);

				if (button == backWnd)
				{
					state->currentPage = state->mainMenu;
					HideSoE(hWnd);
					InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
				}
				else if (button == solveWnd)
				{
					TCHAR solTCHAR[TCHAR_SMALL];
					GetWindowTextW(eqWnd, solTCHAR, TCHAR_SMALL);
					state->currentProblem.clear();
					state->currentProblem.push_back("");
					std::string input = "";
					TCHAR2String(solTCHAR, TCHAR_SMALL, &input);
					if (ValidInput(&input, true))
					{
						state->currentProblem[0] = input;
						bool solved = false;
						while (!solved)
						{
							try
							{
								laStep(&state->currentProblem);
								UserGivePoint(&(state->currentUser));
							}
							catch (const std::exception& e)
							{
								MessageBox(hWnd, L"Unfortunatly, your equation caused an error. This program is in beta, please be gentle.", L"CleverCalc", MB_OK);
							}
							break; // used until laStep gets a full implementation.
						}
						UpdateSolutionWnd(solWnd, &state->currentProblem);
					}
					else
					{
						MessageBox(hWnd, L"Invalid equation(s). Make sure to only include variables x, +, -, numbers, and an equal sign. Curretnly doesn\'t solve every equation.", L"CleverCalc", MB_OK);
					}

				}
				else if (button == stepWnd)
				{
					TCHAR solTCHAR[TCHAR_SMALL];
					std::string input = "";
					GetWindowTextW(eqWnd, solTCHAR, TCHAR_SMALL);
					TCHAR2String(solTCHAR, TCHAR_SMALL, &input);
					if (ValidInput(&input, true))
					{
						if (state->currentProblem.size() == 0)
						{
							state->currentProblem.push_back(input); // if there is no equation, fill the current problem
						}
						else if (input.compare(state->currentProblem[0]) != 0)
						{
							state->currentProblem.clear();
							state->currentProblem.push_back(input);
						} // if the equation changed, clear the current problem		
						try 
						{
							laStep(&state->currentProblem);
							UserGivePoint(&(state->currentUser));
						}
						catch (const std::exception& e)
						{
							MessageBox(hWnd, L"Unfortunatly, your equation caused an error. This program is in beta, please be gentle.", L"CleverCalc", MB_OK);
						}
						
						UpdateSolutionWnd(solWnd, &state->currentProblem);
					}
					else
					{
						MessageBox(hWnd, L"Invalid equation(s). Make sure to only include variables x, +, -, numbers, and an equal sign. Curretnly doesn\'t solve every equation.", L"CleverCalc", MB_OK);
					}

				}
			}
				break;
			case state->stats:
			{
				HWND button = reinterpret_cast<HWND>(lParam);
				TCHAR stats[] = _T("statistics");
				HWND sWnd = FindWindowExW(hWnd, NULL, NULL, stats);

				HWND backWnd = FindWindowExW(hWnd, sWnd, NULL, NULL);
				HWND statsWnd = FindWindowExW(hWnd, backWnd, NULL, NULL);
				HWND weekWnd = FindWindowExW(hWnd, statsWnd, NULL, NULL);
				HWND oneMonthWnd = FindWindowExW(hWnd, weekWnd, NULL, NULL);
				HWND threeMonthWnd = FindWindowExW(hWnd, oneMonthWnd, NULL, NULL);

				if (button == backWnd)
				{
					state->currentPage = state->mainMenu;
					HideStats(hWnd);
					InvalidateRgn(hWnd, NULL, TRUE); // cleans stuff up
				}
				else
				{
					int userID;
					std::ifstream userlistIn;
					std::ofstream userlistOut;
					userlistIn.open(UL, std::ios::in);
					std::string temp, replaceme;

					if (userlistIn.is_open())
					{
						// to start we need to seach previous entries to find the correct user id
						if (userlistIn.beg != userlistIn.end)
						{
							userlistIn.seekg(0, userlistIn.beg);
							for (int i = 0; i < 500; i++) // prevent infinite looping
							{
								if (userlistIn.cur == userlistIn.beg || userlistIn.peek() == '{')
								{
									userlistIn.seekg(1, userlistIn.cur);
									while (userlistIn.peek() != ';')
									{
										temp.push_back(userlistIn.peek());
										userlistIn.seekg(1, userlistIn.cur);
									}
									userID = stoi(temp); // assign current userid
									if (userID == state->currentUser)
									{
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';') // nav to start of points
										{
											//MessageBox(hWnd, L"w1", L"CleverCalc", MB_OK);
											userlistIn.seekg(1, userlistIn.cur);
										}
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';') // nav to start of points
										{
											//MessageBox(hWnd, L"w2", L"CleverCalc", MB_OK);
											userlistIn.seekg(1, userlistIn.cur);
										}
										userlistIn.seekg(1, userlistIn.cur);
										while (userlistIn.peek() != ';') // nav to start of points
										{
											//MessageBox(hWnd, L"w3", L"CleverCalc", MB_OK);
											userlistIn.seekg(1, userlistIn.cur);
										}
										userlistIn.seekg(1, userlistIn.cur);
										temp.clear();
										while (userlistIn.peek() != ';') // nav to end of points and store value
										{
											//MessageBox(hWnd, L"w4", L"CleverCalc", MB_OK);
											temp.push_back(userlistIn.peek());
											userlistIn.seekg(1, userlistIn.cur);
										}

										
									}
									break;
								}
								userlistIn.seekg(1, userlistIn.cur);
							}
						}
						string2TCHAR(&temp, tcentry, 64);
						SetWindowTextW(statsWnd, tcentry);
						userlistIn.close();
					}
				}
			}
				break;
			}
		}
		break;

	case WM_CLOSE: // user has indicated they want to close the window
		if (MessageBox(hWnd, L"Are you sure you want to exit?", L"CleverCalc", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hWnd);
		}
		break;

	case WM_DESTROY: // window is destroyed (no turning back)
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

// winmain, serves as windows application's main()
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	

	// WNDCLASSEX structure, contains window information, such a icon, color, name, etc.
	// contains function pointer to window procedure.
	WNDCLASSEX wcex; // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexw

	wcex.cbSize = sizeof(WNDCLASSEX); // size in bytes of the structure
	wcex.style = CS_HREDRAW | CS_VREDRAW; // class styles: https://learn.microsoft.com/en-us/windows/win32/winmsg/window-class-styles
	wcex.lpfnWndProc = WndProc; // pointer to window procedure
	wcex.cbClsExtra = 0; // "number of extra bytes to allocate following the window-class structure." don't think this will be used.
	wcex.cbWndExtra = 0; // "The number of extra bytes to allocate following the window instance" also set to zero. reread documentation of dialog box is used.
	wcex.hInstance = hInstance; // handle to instance that contains the windo procedure
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION); // handle to the class icon. must be icon resource.
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // handle to cursor resource. if null curso must be explicitly set
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // handle to background brush. or color value.
	wcex.lpszMenuName = NULL; // pointer to terminated char string that specifies the resource name of the class menu. NULL means no default menu.
	wcex.lpszClassName = szWindowClass; // "pointer to a null-terminated string or is an atom" 
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION); // small icon

	// register WNDCLASSEX with windows. _T iis used because of TCHAR
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"), // dialog
			_T("CleverCalc"), // title
			NULL);
		
		return 1;
	}

	// initialize program state
	StateInfo *state = new (std::nothrow) StateInfo; //create a 
	if (state == NULL)
	{
		return 0;
	}

	state->currentPage = state->home; //sets the current page to home.


	// creating a window:
	HWND hWnd = CreateWindowEx( // hwnd is handle to window
		WS_EX_OVERLAPPEDWINDOW, // optional window style, this is a standard window and has all bells and wistles
		szWindowClass, // name of application
		szTitle, // text in title bar
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, // type of window see first parameter, with no maximize box or thick frame so no resizes.
		CW_USEDEFAULT, CW_USEDEFAULT, // initial position x,y
		W_WIDTH, W_HIGHT, // initial size w,h
		NULL, // parent window
		NULL, // for menu bars
		hInstance, // winmain parameter used here
		state // application state
	);
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindowEx failed!"),
			_T("CleverCalc"),
			NULL);

		return 1;
	}

	
	ShowWindow(hWnd, // window handle
		nCmdShow); // winmain parameter
	UpdateWindow(hWnd);

	CreateHomeWnds(hWnd, nCmdShow);
	CreateMainMenuWnds(hWnd, nCmdShow);
	CreateRegisterWnds(hWnd, nCmdShow);
	CreateForgotWnds(hWnd, nCmdShow);
	CreateLAWnds(hWnd, nCmdShow);
	CreateSoEWnds(hWnd, nCmdShow);
	CreateStatsWbds(hWnd, nCmdShow);

	// message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // kestroke message to character message
		DispatchMessage(&msg); // dispatches message to window procedure
	}

	return (int)msg.wParam;
}
