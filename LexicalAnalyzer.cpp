#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

FILE *output = fopen("output.txt", "w");

//소스 코드를 불러올 버퍼 
char Code[50] = {0};
//현재 읽고 있는 문자의 위치를 가리키는 인덱스 
int index = 0;
int T_index = 0; 	//앞선 DFA에 해당되지 않을 경우, 전역변수 index를
					//원래대로 돌려놓기 위한 변수. 

//DFA table 
int Keyword[21][12] = {0, };
int VType[17][11] = {0, };
int Operator[12][9] = {0, };
int Comparison[6][4] = {0, };
int Identifier[6][3] = {0, };
int Integer[5][4] = {0, };
int String[6][4] = {0, };
int Boolean[9][8] = {0, };
int Float[8][5] = {0, };
int PuncSym[7][6] = {0, };
int WS[3][2] = {0, };

void InitDFA()
{
	//DFA Keyword
	Keyword[0][0] = 1;
	Keyword[0][1] = 2;
	Keyword[0][2] = 3;
	Keyword[0][3] = 4;
	Keyword[0][4] = 5;
	Keyword[1][3] = 6;
	Keyword[2][5] = 7;
	Keyword[3][6] = 8;
	Keyword[4][7] = 9;
	Keyword[5][1] = 10;
	Keyword[7][8] = 11;
	Keyword[8][0] = 12;
	Keyword[9][4] = 13;
	Keyword[10][9] = 14;
	Keyword[11][1] = 15;
	Keyword[12][5] = 16;
	Keyword[14][10] = 17;
	Keyword[16][1] = 18;
	Keyword[17][4] = 19;
	Keyword[19][11] = 20;
	
	//DFA Variable Type
	VType[0][0] = 1;
	VType[0][1] = 2;
	VType[0][2] = 3;
	VType[0][3] = 4;
	VType[1][4] = 5;
	VType[2][5] = 6;
	VType[3][6] = 7;
	VType[4][7] = 8;
	VType[5][8] = 9;
	VType[6][9] = 10;
	VType[7][6] = 11;
	VType[8][6] = 12;
	VType[10][10] = 13;
	VType[11][7] = 14;
	VType[12][9] = 15;
	VType[15][8] = 16;
	
	//DFA Operator
	Operator[0][0] = 1; 
	Operator[0][1] = 2; 
	Operator[0][2] = 3; 
	Operator[0][3] = 4; 
	Operator[0][4] = 5; 
	Operator[0][5] = 6; 
	Operator[0][6] = 7; 
	Operator[0][7] = 8; 
	Operator[0][8] = 9; 
	Operator[5][4] = 10;
	Operator[6][5] = 11;  
	
	//DFA Comparison
	Comparison[0][0] = 1;
	Comparison[0][1] = 2;
	Comparison[0][2] = 3;
	Comparison[0][3] = 4;
	Comparison[1][2] = 5;
	Comparison[2][2] = 5;
	Comparison[3][2] = 5;
	Comparison[4][2] = 5;
	
	//DFA Identifier
	Identifier[0][0] = 1; 
	Identifier[0][1] = 2;
	Identifier[1][0] = 3;
	Identifier[1][1] = 4;
	Identifier[1][2] = 5;
	Identifier[2][0] = 3;
	Identifier[2][1] = 4;
	Identifier[2][2] = 5;
	Identifier[3][0] = 3;
	Identifier[3][1] = 4;
	Identifier[3][2] = 5;
	Identifier[4][0] = 3;
	Identifier[4][1] = 4;
	Identifier[4][2] = 5;
	Identifier[5][0] = 3;
	Identifier[5][1] = 4;
	Identifier[5][2] = 5;
	
	//DFA Integer
	Integer[0][0] = 1;
	Integer[0][1] = 2;
	Integer[0][3] = 3;
	Integer[1][1] = 2;
	Integer[2][2] = 4;
	Integer[4][2] = 4;
	
	//DFA String
	String[0][0] = 1;
	String[1][1] = 2;
	String[1][2] = 3;
	String[1][3] = 4;
	String[2][0] = 5;
	String[2][1] = 2;
	String[2][2] = 3;
	String[2][3] = 4;
	String[3][0] = 5;
	String[3][1] = 2;
	String[3][2] = 3;
	String[3][3] = 4;
	String[4][0] = 5;
	String[4][1] = 2;
	String[4][2] = 3;
	String[4][3] = 4;
	
	//DFA Boolean
	Boolean[0][0] = 1;
	Boolean[0][1] = 2;
	Boolean[1][2] = 3;
	Boolean[2][3] = 4;
	Boolean[3][4] = 5;
	Boolean[4][5] = 6;
	Boolean[5][6] = 8;
	Boolean[6][7] = 7;
	Boolean[7][6] = 8;
	
	//DFA Float
	Float[0][0] = 1;
	Float[0][1] = 2;
	Float[0][2] = 3;
	Float[1][1] = 2;
	Float[1][2] = 3;
	Float[2][3] = 2;
	Float[2][4] = 4;
	Float[3][4] = 4;
	Float[4][1] = 6;
	Float[4][2] = 5;
	Float[5][1] = 6;
	Float[5][2] = 7;
	Float[6][1] = 6;
	Float[6][2] = 7;
	Float[7][1] = 6;
	Float[7][2] = 7;
	
	//DFA Punctuation Symbol
	PuncSym[0][0] = 1;
	PuncSym[0][1] = 2;
	PuncSym[0][2] = 3;
	PuncSym[0][3] = 4;
	PuncSym[0][4] = 5;
	PuncSym[0][5] = 6;
	
	//DFA White Space
	WS[0][0] = 1;
	WS[0][1] = 2;
	WS[1][0] = 1;
	WS[1][1] = 2;
	WS[2][0] = 1;
	WS[2][1] = 2;
}

//DFA Keyword 
int Check_Tstate_Keyword(int Tstate)
{
	//문자열이 Keyword에 포함되면 1 반환, 그렇지 않으면 0 반환 
	if (Tstate == 6) {
		fprintf(output, "<IF>\n");
		return 1;
	}
	else if (Tstate == 15) {
		fprintf(output, "<ELSE>\n");
		return 1;
	}
	else if (Tstate == 18) {
		fprintf(output, "<WHILE>\n");
		return 1;
	}
	else if (Tstate == 13) {
		fprintf(output, "<FOR>\n");
		return 1;
	}
	else if (Tstate == 20) {
		fprintf(output, "<RETURN>\n");
		return 1;
	}
	
	return 0;
}
int DFA_Check_Keyword()
{
	int Tstate = 0;
	
	while(1)	//return될 때까지 반복 
	{
		if (Code[index] == 'i') {
			if (Keyword[Tstate][0] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][0];
				index++;
			}
		}	
		else if (Code[index] == 'e') {
			if (Keyword[Tstate][1] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][1];
				index++;
			}
		}
		else if (Code[index] == 'w') {
			if (Keyword[Tstate][2] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][2];
				index++;
			}
		}
		else if (Code[index] == 'f') {
			if (Keyword[Tstate][3] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][3];
				index++;
			}
		}
		else if (Code[index] == 'r') {
			if (Keyword[Tstate][4] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][4];
				index++;
			}	
		}
		else if (Code[index] == 'l') {
			if (Keyword[Tstate][5] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][5];
				index++;
			}	
		}
		else if (Code[index] == 'h') {
			if (Keyword[Tstate][6] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][6];
				index++;
			}
		}
		else if (Code[index] == 'o') {
			if (Keyword[Tstate][7] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][7];
				index++;
			}
		}
		else if (Code[index] == 's') {
			if (Keyword[Tstate][8] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][8];
				index++;
			}
		}
		else if (Code[index] == 't') {
			if (Keyword[Tstate][9] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][9];
				index++;
			}
		}
		else if (Code[index] == 'u') {
			if (Keyword[Tstate][10] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][10];
				index++;
			}	
		}
		else if (Code[index] == 'n') {
			if (Keyword[Tstate][11] == 0)
				return Check_Tstate_Keyword(Tstate);
			else {
				Tstate = Keyword[Tstate][11];
				index++;
			}	
		}
		else
			return Check_Tstate_Keyword(Tstate);
	}
}

//DFA VType
int Check_Tstate_VType(int Tstate)
{
	//문자열이 VType에 포함되면 1 반환, 그렇지 않으면 0 반환 
	if (Tstate == 9) {
		fprintf(output, "<TYPE_INT>\n");
		return 1;
	}
	else if (Tstate == 13) {
		fprintf(output, "<TYPE_CHAR>\n");
		return 1;
	}
	else if (Tstate == 14) {
		fprintf(output,"<TYPE_BOOL>\n");
		return 1;
	}
	else if (Tstate == 16) {
		fprintf(output, "<TYPE_FLOAT>\n");
		return 1;
	}

	return 0;
}
int DFA_Check_VType()
{
	int Tstate = 0;
	
	while(1)	//return될 때까지 반복 
	{
		if (Code[index] == 'i') {
			if (VType[Tstate][0] == 0)
				return Check_Tstate_VType(Tstate);
			else {
				Tstate = VType[Tstate][0];
				index++;
			}
		}	
		else if (Code[index] == 'c') {
			if (VType[Tstate][1] == 0)
				return Check_Tstate_VType(Tstate);
			else {
				Tstate = VType[Tstate][1];
				index++;
			}
		}
		else if (Code[index] == 'b') {
			if (VType[Tstate][2] == 0)
				return Check_Tstate_VType(Tstate);
			else {
				Tstate = VType[Tstate][2];
				index++;
			}
		}
		else if (Code[index] == 'f') {
			if (VType[Tstate][3] == 0)
				return Check_Tstate_VType(Tstate);
			else {
				Tstate = VType[Tstate][3];
				index++;
			}
		}
		else if (Code[index] == 'n') {
			if (VType[Tstate][4] == 0)
				return Check_Tstate_VType(Tstate);
			else {
				Tstate = VType[Tstate][4];
				index++;
			}	
		}
		else if (Code[index] == 'h') {
			if (VType[Tstate][5] == 0)
				return Check_Tstate_VType(Tstate);
			else {
				Tstate = VType[Tstate][5];
				index++;
			}	
		}
		else if (Code[index] == 'o') {
			if (VType[Tstate][6] == 0)
				return Check_Tstate_VType(Tstate);
			else {
				Tstate = VType[Tstate][6];
				index++;
			}
		}
		else if (Code[index] == 'l') {
			if (VType[Tstate][7] == 0)
				return Check_Tstate_VType(Tstate);
			else {
				Tstate = VType[Tstate][7];
				index++;
			}
		}
		else if (Code[index] == 't') {
			if (VType[Tstate][8] == 0)
				return Check_Tstate_VType(Tstate);
			else {
				Tstate = VType[Tstate][8];
				index++;
			}
		}
		else if (Code[index] == 'a') {
			if (VType[Tstate][9] == 0)
				return Check_Tstate_VType(Tstate);
			else {
				Tstate = VType[Tstate][9];
				index++;
			}
		}
		else if (Code[index] == 'r') {
			if (VType[Tstate][10] == 0)
				return Check_Tstate_VType(Tstate);
			else {
				Tstate = VType[Tstate][10];
				index++;
			}	
		}
		else
			return Check_Tstate_VType(Tstate);
	}
}

//DFA Operator
int Check_Tstate_Operator(int Tstate)
{
	//문자열이 Operator에 포함되면 1 반환, 그렇지 않으면 0 반환 
	if (Tstate == 1) {
		fprintf(output, "<ADD>\n");
		return 1;
	}
	else if (Tstate == 2) {
		fprintf(output, "<SUB>\n");
		return 1;
	}
	else if (Tstate == 3) {
		fprintf(output, "<MUL>\n");
		return 1;
	}
	else if (Tstate == 4) {
		fprintf(output, "<DIV>\n");
		return 1;
	}
	else if (Tstate == 10) {
		fprintf(output, "<LSHIFT>\n");
		return 1;
	}
	else if (Tstate == 11) {
		fprintf(output, "<RSHIFT>\n");
		return 1;
	}
	else if (Tstate == 7) {
		fprintf(output, "<AND>\n");
		return 1;
	}
	else if (Tstate == 8) {
		fprintf(output, "<OR>\n");
		return 1;
	}
	else if (Tstate == 9) {
		fprintf(output, "<ASSIGN>\n");
		return 1;
	}

	return 0;
}
int DFA_Check_Operator()
{
	int Tstate = 0;
	
	while(1)	//return될 때까지 반복 
	{
		if (Code[index] == '+') {
			if (Operator[Tstate][0] == 0)
				return Check_Tstate_Operator(Tstate);
			else {
				Tstate = Operator[Tstate][0];
				index++;
			}
		}	
		else if (Code[index] == '-') {
			if (Operator[Tstate][1] == 0)
				return Check_Tstate_Operator(Tstate);
			else {
				Tstate = Operator[Tstate][1];
				index++;
			}
		}
		else if (Code[index] == '*') {
			if (Operator[Tstate][2] == 0)
				return Check_Tstate_Operator(Tstate);
			else {
				Tstate = Operator[Tstate][2];
				index++;
			}
		}
		else if (Code[index] == '/') {
			if (Operator[Tstate][3] == 0)
				return Check_Tstate_Operator(Tstate);
			else {
				Tstate = Operator[Tstate][3];
				index++;
			}
		}
		else if (Code[index] == '<') {
			if (Operator[Tstate][4] == 0)
				return Check_Tstate_Operator(Tstate);
			else {
				Tstate = Operator[Tstate][4];
				index++;
			}	
		}
		else if (Code[index] == '>') {
			if (Operator[Tstate][5] == 0)
				return Check_Tstate_Operator(Tstate);
			else {
				Tstate = Operator[Tstate][5];
				index++;
			}	
		}
		else if (Code[index] == '&') {
			if (Operator[Tstate][6] == 0)
				return Check_Tstate_Operator(Tstate);
			else {
				Tstate = Operator[Tstate][6];
				index++;
			}
		}
		else if (Code[index] == '|') {
			if (Operator[Tstate][7] == 0)
				return Check_Tstate_Operator(Tstate);
			else {
				Tstate = Operator[Tstate][7];
				index++;
			}
		}
		else if (Code[index] == '=') {
			if (Operator[Tstate][8] == 0)
				return Check_Tstate_Operator(Tstate);
			else {
				Tstate = Operator[Tstate][8];
				index++;
			}
		}
		else
			return Check_Tstate_Operator(Tstate);
	}
}

//DFA Comparison
int Check_Tstate_Comparison(int Tstate)
{
	//문자열이 Comparison에 포함되면 1 반환, 그렇지 않으면 0 반환 
	if ((Tstate == 1) | (Tstate == 2) | (Tstate == 5)) {
		fprintf(output, "<COMPARE, ");
		for(int i=T_index; i<index; i++) {
			fprintf(output, "%c>\n", Code[i]);
		}
		return 1;
	}

	return 0;
}
int DFA_Check_Comparison()
{
	int Tstate = 0;
	
	while(1)	//return될 때까지 반복 
	{
		if (Code[index] == '<') {
			if (Comparison[Tstate][0] == 0)
				return Check_Tstate_Comparison(Tstate);
			else {
				Tstate = Comparison[Tstate][0];
				index++;
			}
		}	
		else if (Code[index] == '>') {
			if (Comparison[Tstate][1] == 0)
				return Check_Tstate_Comparison(Tstate);
			else {
				Tstate = Comparison[Tstate][1];
				index++;
			}
		}
		else if (Code[index] == '=') {
			if (Comparison[Tstate][2] == 0)
				return Check_Tstate_Comparison(Tstate);
			else {
				Tstate = Comparison[Tstate][2];
				index++;
			}
		}
		else if (Code[index] == '!') {
			if (Comparison[Tstate][3] == 0)
				return Check_Tstate_Comparison(Tstate);
			else {
				Tstate = Comparison[Tstate][3];
				index++;
			}
		}
		else
			return Check_Tstate_Comparison(Tstate);
	}
}

//DFA Identifier
int Check_Tstate_Identifier(int Tstate)
{
	//문자열이 Identifier에 포함되면 1 반환, 그렇지 않으면 0 반환 
	if ((Tstate == 1) | (Tstate == 2) | (Tstate == 3) | (Tstate == 4) | (Tstate == 5)) {
		fprintf(output, "<ID, ");
		for(int i=T_index; i<index; i++) {
			fprintf(output, "%c", Code[i]);
		}
		fprintf(output, ">\n");
		return 1;
	}

	return 0;
}
int DFA_Check_Identifier()
{
	int Tstate = 0;
	
	while(1)	//return될 때까지 반복 
	{
		//Letter
		if ((Code[index]>='a') && (Code[index]<='z')) {
			if (Identifier[Tstate][0] == 0)
				return Check_Tstate_Identifier(Tstate);
			else {
				Tstate = Identifier[Tstate][0];
				index++;
			}
		}
		else if ((Code[index]>='A') && (Code[index]<='Z')) {
			if (Identifier[Tstate][0] == 0)
				return Check_Tstate_Identifier(Tstate);
			else {
				Tstate = Identifier[Tstate][0];
				index++;
			}
		}
		else if (Code[index] == '_') {
			if (Identifier[Tstate][1] == 0)
				return Check_Tstate_Identifier(Tstate);
			else {
				Tstate = Identifier[Tstate][1];
				index++;
			}
		}
		else if ((Code[index]>='0') && (Code[index]<='9')) {
			if (Identifier[Tstate][2] == 0)
				return Check_Tstate_Identifier(Tstate);
			else {
				Tstate = Identifier[Tstate][2];
				index++;
			}
		}
		else
			return Check_Tstate_Identifier(Tstate);
	}
}

//DFA Integer
int Check_Tstate_Integer(int Tstate)
{
	//문자열이 Integer에 포함되면 1 반환, 그렇지 않으면 0 반환 
	if ((Tstate == 3) | (Tstate == 4) | (Tstate == 2)) {
		fprintf(output, "<INTEGER, ");
		for(int i=T_index; i<index; i++) {
			fprintf(output, "%c", Code[i]);
		}
		fprintf(output, ">\n");
		return 1;
	}
	return 0;
}
int DFA_Check_Integer()
{
	int Tstate = 0;
	
	while(1)	//return될 때까지 반복 
	{
		if (Tstate == 2 | Tstate == 4)
		{
			//Digit
			if (Code[index]>='0' && Code[index]<='9') {
				if (Integer[Tstate][2] == 0)
					return Check_Tstate_Integer(Tstate);
				else {
					Tstate = Integer[Tstate][2];
					index++;
				}
			}
			else
				return Check_Tstate_Integer(Tstate);
		}
		else
		{
			//-
			if (Code[index] == '-') {
				if (Integer[Tstate][0] == 0)
					return Check_Tstate_Integer(Tstate);
				else {
					Tstate = Integer[Tstate][0];
					index++;
				}
			}
			//NonZero	
			else if (Code[index]>='1' && Code[index]<='9') {
				if (Integer[Tstate][1] == 0)
					return Check_Tstate_Integer(Tstate);
				else {
					Tstate = Integer[Tstate][1];
					index++;
				}
			}
			//Zero
			else if (Code[index] == '0') {
				if (Integer[Tstate][3] == 0)
					return Check_Tstate_Integer(Tstate);
				else {
					Tstate = Integer[Tstate][3];
					index++;
				}
			}
			else
				return Check_Tstate_Integer(Tstate);
		}
	}
}


//DFA String
int Check_Tstate_String(int Tstate)
{
	//문자열이 String에 포함되면 1 반환, 그렇지 않으면 0 반환 
	if (Tstate == 5) {
		fprintf(output, "<STRING, ");
		for(int i=T_index; i<index; i++) {
			fprintf(output, "%c", Code[i]);
		}
		fprintf(output, ">\n");
		return 1;
	}

	return 0;
}
int DFA_Check_String()
{
	int Tstate = 0;
	
	while(1)	//return될 때까지 반복 
	{
		//"
		if (Code[index] == '"') {
			if (String[Tstate][0] == 0)
				return Check_Tstate_String(Tstate);
			else {
				Tstate = String[Tstate][0];
				index++;
			}
		}
		//Letter
		else if ((Code[index]>='a') && (Code[index]<='z')) {
			if (String[Tstate][1] == 0)
				return Check_Tstate_String(Tstate);
			else {
				Tstate = String[Tstate][1];
				index++;
			}
		}
		else if ((Code[index]>='A') && (Code[index]<='Z')) {
			if (String[Tstate][1] == 0)
				return Check_Tstate_String(Tstate);
			else {
				Tstate = String[Tstate][1];
				index++;
			}
		}
		//Digit
		else if ((Code[index]>='0') && (Code[index]<='9')) {
			if (String[Tstate][2] == 0)
				return Check_Tstate_String(Tstate);
			else {
				Tstate = String[Tstate][2];
				index++;
			}
		}
		//blank
		else if (Code[index] == ' ') {
			if (String[Tstate][3] == 0)
				return Check_Tstate_String(Tstate);
			else {
				Tstate = String[Tstate][3];
				index++;
			}
		}
		else
			return Check_Tstate_String(Tstate);
	}
}

//DFA Boolean
int Check_Tstate_Boolean(int Tstate)
{
	//문자열이 Boolean에 포함되면 1 반환, 그렇지 않으면 0 반환 
	if (Tstate == 8) {
		fprintf(output, "<BOOLEAN, ");
		for(int i=T_index; i<index; i++) {
			fprintf(output, "%c", Code[i]);
		}
		fprintf(output, ">\n");
		return 1;
	}

	return 0;
}
int DFA_Check_Boolean()
{
	int Tstate = 0;
	
		while(1)	//return될 때까지 반복 
	{
		if (Code[index] == 't') {
			if (Boolean[Tstate][0] == 0)
				return Check_Tstate_Boolean(Tstate);
			else {
				Tstate = Boolean[Tstate][0];
				index++;
			}
		}	
		else if (Code[index] == 'f') {
			if (Boolean[Tstate][1] == 0)
				return Check_Tstate_Boolean(Tstate);
			else {
				Tstate = Boolean[Tstate][1];
				index++;
			}
		}
		else if (Code[index] == 'r') {
			if (Boolean[Tstate][2] == 0)
				return Check_Tstate_Boolean(Tstate);
			else {
				Tstate = Boolean[Tstate][2];
				index++;
			}
		}
		else if (Code[index] == 'a') {
			if (Boolean[Tstate][3] == 0)
				return Check_Tstate_Boolean(Tstate);
			else {
				Tstate = Boolean[Tstate][3];
				index++;
			}
		}
		else if (Code[index] == 'u') {
			if (Boolean[Tstate][4] == 0)
				return Check_Tstate_Boolean(Tstate);
			else {
				Tstate = Boolean[Tstate][4];
				index++;
			}	
		}
		else if (Code[index] == 'l') {
			if (Boolean[Tstate][5] == 0)
				return Check_Tstate_Boolean(Tstate);
			else {
				Tstate = Boolean[Tstate][5];
				index++;
			}	
		}
		else if (Code[index] == 'e') {
			if (Boolean[Tstate][6] == 0)
				return Check_Tstate_Boolean(Tstate);
			else {
				Tstate = Boolean[Tstate][6];
				index++;
			}
		}
		else if (Code[index] == 's') {
			if (Boolean[Tstate][7] == 0)
				return Check_Tstate_Boolean(Tstate);
			else {
				Tstate = Boolean[Tstate][7];
				index++;
			}
		}
		else
			return Check_Tstate_Boolean(Tstate);
	}
}


//DFA Float
int Check_Tstate_Float(int Tstate)
{
	//문자열이 Float에 포함되면 1 반환, 그렇지 않으면 0 반환 
	if ((Tstate == 5) | (Tstate == 6)) {
		fprintf(output, "<Float, ");
		for(int i=T_index; i<index; i++) {
			fprintf(output, "%c", Code[i]);
		}
		fprintf(output, ">\n");
		return 1;
	}
	return 0;
}
int DFA_Check_Float()
{
	int Tstate = 0;
	
	while(1)	//return될 때까지 반복 
	{
		if (Tstate == 2)
		{
			//Digit
			if (Code[index]>='0' && Code[index]<='9') {
				if (Float[Tstate][3] == 0)
					return Check_Tstate_Float(Tstate);
				else {
					Tstate = Float[Tstate][3];
					index++;
				}
			}
			//.
			else if (Code[index] == '0') {
				if (Float[Tstate][4] == 0)
					return Check_Tstate_Float(Tstate);
				else {
					Tstate = Float[Tstate][4];
					index++;
				}
			}
			else
				return Check_Tstate_Float(Tstate);
		}
		else
		{
			//-
			if (Code[index] == '-') {
				if (Float[Tstate][0] == 0)
					return Check_Tstate_Float(Tstate);
				else {
					Tstate = Float[Tstate][0];
					index++;
				}
			}
			//NonZero	
			else if (Code[index]>='1' && Code[index]<='9') {
				if (Float[Tstate][1] == 0)
					return Check_Tstate_Float(Tstate);
				else {
					Tstate = Float[Tstate][1];
					index++;
				}
			}
			//Zero
			else if (Code[index] == '0') {
				if (Float[Tstate][2] == 0)
					return Check_Tstate_Float(Tstate);
				else {
					Tstate = Float[Tstate][2];
					index++;
				}
			}
			//.
			else if (Code[index] == '.') {
				if (Float[Tstate][4] == 0)
					return Check_Tstate_Float(Tstate);
				else {
					Tstate = Float[Tstate][4];
					index++;
				}
			}
			else
				return Check_Tstate_Float(Tstate);
		}
		
	}
}

//DFA PuncSym
int Check_Tstate_PuncSym(int Tstate)
{
	//문자열이 PuncSym에 포함되면 1 반환, 그렇지 않으면 0 반환 
	if (Tstate == 1) {
		fprintf(output, "<SEMMI>\n");
		return 1;
	}
	else if (Tstate == 2) {
		fprintf(output, "<LPAREN>\n");
		return 1;
	}
	else if (Tstate == 3) {
		fprintf(output, "<RPAREN>\n");
		return 1;
	}
	else if (Tstate == 4) {
		fprintf(output, "<LBRACE>\n");
		return 1;
	}
	else if (Tstate == 5) {
		fprintf(output, "<RBRACE>\n");
		return 1;
	}
	else if (Tstate == 6) {
		fprintf(output, "<COMMA>\n");
		return 1;
	}

	return 0;
}
int DFA_Check_PuncSym()
{
	int Tstate = 0;
	
	while(1)	//return될 때까지 반복 
	{
		if (Code[index] == ';') {
			if (PuncSym[Tstate][0] == 0)
				return Check_Tstate_PuncSym(Tstate);
			else {
				Tstate = PuncSym[Tstate][0];
				index++;
			}
		}	
		else if (Code[index] == '(') {
			if (PuncSym[Tstate][1] == 0)
				return Check_Tstate_PuncSym(Tstate);
			else {
				Tstate = PuncSym[Tstate][1];
				index++;
			}
		}
		else if (Code[index] == ')') {
			if (PuncSym[Tstate][2] == 0)
				return Check_Tstate_PuncSym(Tstate);
			else {
				Tstate = PuncSym[Tstate][2];
				index++;
			}
		}
		else if (Code[index] == '{') {
			if (PuncSym[Tstate][3] == 0)
				return Check_Tstate_PuncSym(Tstate);
			else {
				Tstate = PuncSym[Tstate][3];
				index++;
			}
		}
		else if (Code[index] == '}') {
			if (PuncSym[Tstate][4] == 0)
				return Check_Tstate_PuncSym(Tstate);
			else {
				Tstate = PuncSym[Tstate][4];
				index++;
			}	
		}
		else if (Code[index] == ',') {
			if (PuncSym[Tstate][5] == 0)
				return Check_Tstate_PuncSym(Tstate);
			else {
				Tstate = PuncSym[Tstate][5];
				index++;
			}	
		}
		else
			return Check_Tstate_PuncSym(Tstate);
	}
}

//DFA WS
int Check_Tstate_WS(int Tstate)
{
	//문자열이 WS에 포함되면 1 반환, 그렇지 않으면 0 반환 
	if (Tstate == 1) {
		fprintf(output, "<WS>\n");
		return 1;
	}
	return 0;
}
int DFA_Check_WS()
{
	int Tstate = 0;
	
	while(1)	//return될 때까지 반복 
	{
		if ((Code[index] == '\t') | (Code[index] == ' ')) {
			if (WS[Tstate][0] == 0)
				return Check_Tstate_WS(Tstate);
			else {
				Tstate = WS[Tstate][0];
				index++;
			}
		}	
		else if (Code[index] == '\n') {
			if (WS[Tstate][1] == 0)
				return Check_Tstate_WS(Tstate);
			else {
				Tstate = WS[Tstate][1];
				index++;
			}
		}
		else
			return Check_Tstate_WS(Tstate);
	}
}

int main()
{
	//DFA 테이블 초기화 
	InitDFA();

	//Code 문자열에 소스 코드 가져옴.
    FILE *input = fopen("input.c", "r");
    fgets(Code, sizeof(Code), input);
    
    FILE *output = fopen("output.txt", "w");
	
	int k = 0;	//앞선 DFA에 해당되는지 체크하는 변수.
				//1이면 우선순위 DFS에 해당된다. 
	int i = 50;
	while(i>0)
	{i--;
		//WS
		k = DFA_Check_WS();
		//Keyword	
		if (!k) {
			index = T_index;
			k = DFA_Check_Keyword();
		}
		//VType
		if (!k) {
			index = T_index;
			k = DFA_Check_VType();
		}
		//Boolean
		if (!k) {
			index = T_index;
			k = DFA_Check_Boolean();
		}
		//PuncSym
		if (!k) {
			index = T_index;
			k = DFA_Check_PuncSym();
		}
		//String
		if (!k) {
			index = T_index;
			k = DFA_Check_String();
		}
		//Float
		if (!k) {
			index = T_index;
			k = DFA_Check_Float();
		}
		//Integer
		if (!k) {
			index = T_index;
			k = DFA_Check_Integer();
		}
		//Comparison
		if (!k) {
			index = T_index;
			k = DFA_Check_Comparison();
		}
		//Operator
		if (!k) {
			index = T_index;
			k = DFA_Check_Operator();
		}
		//Identifier
		if (!k) {
			index = T_index;
			k = DFA_Check_Identifier();
		}
		
		T_index = index;
	}
	
	fclose(input);    // 파일 포인터 닫기
	fclose(output);
}
