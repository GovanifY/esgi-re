#include "morse.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_LEN 10
char num[][5] = {
	{'a','a','a','a','a'},//0
	{'z','a','a','a','a'},//1
	{'z','z','a','a','a'},//2
	{'z','z','z','a','a'},//3
	{'z','z','z','z','a'},//4
	{'z','z','z','z','z'},//5
	{'a','z','z','z','z'},//6
	{'a','a','z','z','z'},//7
	{'a','a','a','z','z'},//8
	{'a','a','a','a','z'} //9
};


#define MARK_LEN 17
char mark[][8] = {
	{'z', 'a', 'z', 'a', 'z', 'a', '*', 'z'},//z	0
	{'a', 'a', 'a', 'z', 'z', 'z', '*', ':'},//:
	{'a', 'a', 'z', 'z', 'a', 'a', '*', ','},//,
	{'a', 'z', 'a', 'z', 'a', 'z', '*', ';'},//;
	{'z', 'z', 'a', 'a', 'z', 'z', '*', '?'},//?
	{'a', 'z', 'z', 'z', 'a', '*', '*', '='},//=
	{'z', 'a', 'a', 'a', 'a', 'z', '*', '\''},//'
	{'a', 'z', 'z', 'a', 'z', '*', '*', '/'},///
	{'a', 'z', 'a', 'z', 'a', 'a', '*', '!'},//!
	{'a', 'z', 'z', 'z', 'z', 'a', '*', 'a'},//a
	{'z', 'z', 'a', 'a', 'z', 'a', '*', '_'},//_
	{'z', 'a', 'z', 'z', 'a', 'z', '*', '"'},//"
	{'a', 'z', 'a', 'a', 'z', '*', '*', '('},//(
	{'a', 'z', 'a', 'a', 'z', 'a', '*', ')'},//)
	{'z', 'z', 'z', 'a', 'z', 'z', 'a', '$'},//$
	{'z', 'a', 'z', 'z', 'z', '*', '*', '&'},//&
	{'z', 'a', 'a', 'z', 'a', 'z', '*', '@'} //@	16
};

#define CHARACTER_LEN 26
char a2[][4] = {
{'z','a','*','*'},//A
{'a','z','z','z'},//B
{'a','z','a','z'},//C
{'a','z','z','*'},//D
{'z','*','*','*'},//E
{'z','z','a','z'},//F
{'a','a','z','*'},//G
{'z','z','z','z'},//H
{'z','z','*','*'},//I
{'z','a','a','a'},//J
{'a','z','a','*'},//K
{'z','a','z','z'},//L
{'a','a','*','*'},//M
{'a','z','*','*'},//N
{'a','a','a','*'},//O
{'z','a','a','z'},//P
{'a','a','z','a'},//Q
{'z','a','z','*'},//R
{'z','z','z','*'},//S
{'a','*','*','*'},//T
{'z','z','a','*'},//U
{'z','z','z','a'},//V
{'z','a','a','*'},//W
{'a','z','z','a'},//X
{'a','z','a','a'},//Y
{'a','a','z','z'} //Z
};

Morse_t* new_morse() {
	Morse_t *ret;
	ret = (Morse_t*)malloc(sizeof(Morse_t));
	memset(ret->c, 0, 9);
	return ret;
}


/*
 *	MARK
 */
bool mark2morse(char n, Morse_t *morse) {
	int a = 0;

	for (; a < MARK_LEN; a++) {
		if (mark[a][7] == n) {
			morse->c[0] = mark[a][0];
			morse->c[1] = mark[a][1];
			morse->c[2] = mark[a][2];
			morse->c[3] = mark[a][3];
			morse->c[4] = mark[a][4];
			morse->c[5] = mark[a][5];
			morse->c[6] = mark[a][6];
			return true;
		}
	}
	return false;
}

bool morse2mark(Morse_t *morse, char *n) {
	int a = 0;
	for (; a < MARK_LEN; a++) {
		if (mark[a][0] == morse->c[0] &&
			mark[a][1] == morse->c[1] &&
			mark[a][2] == morse->c[2] &&
			mark[a][3] == morse->c[3] &&
			mark[a][4] == morse->c[4] &&
			mark[a][5] == morse->c[5] &&
			mark[a][6] == morse->c[6] ) {

			*n = mark[a][7];
			return true;
		}
	}
	return false;
}

/*
 *	NUMBER
 */
bool num2morse(char n, Morse_t *morse) {
	int pos = n - 48;

	if (pos <= 9 && pos >= 0) {
		morse->c[0] = num[pos][0];
		morse->c[1] = num[pos][1];
		morse->c[2] = num[pos][2];
		morse->c[3] = num[pos][3];
		morse->c[4] = num[pos][4];  
		return true;
	} 
	return false;
}

bool morse2num(Morse_t *morse, char *n) {
	int i = 0;

	for (; i < NUM_LEN; i++) {
		if (num[i][0] == morse->c[0] &&
			num[i][1] == morse->c[1] &&
			num[i][2] == morse->c[2] &&
			num[i][3] == morse->c[3] &&
			num[i][4] == morse->c[4] ) {

			*n = (char)(i + 48);
			return true;
		}
	}
	return false;
}

/*
 *	CHARACTER
 */
bool str2morse(char m , Morse_t *morse) {
	int pos = m - 97;
	if (pos >= 0 && pos <= 25) {
	morse->c[0] = a2[pos][0];
	morse->c[1] = a2[pos][1];
	morse->c[2] = a2[pos][2];	
	morse->c[3] = a2[pos][3];
		return true;
	}
	return false;
}


bool morse2str(Morse_t *morse, char *ch) {
	int i = 0;
	for (i = 0; i < CHARACTER_LEN; i++) {
		if (a2[i][0] == morse->c[0] &&
			a2[i][1] == morse->c[1] &&
			a2[i][2] == morse->c[2] &&
			a2[i][3] == morse->c[3]) { 

			*ch =  (char)(i + 97);
			return true;
		}
	}
	return false;
}


void morse_str_to_str(char *morse ,char *string, int buf_len) {
	Morse_t *temp = new_morse();
	int a = 0;
	int b = 0;
	int c = 0;
	int len = 0;
	char ch = '*';

	memset(temp->c, '*', 8);//fill the morse-array with '*'
	len = strlen(morse);

	for ( ; a < len; a ++) {
		if (c > buf_len) {
			return;
		}

		if (morse[a] != SEPARATOR && morse[a] != FAKE_SPACE)
			temp->c[b++] = morse[a];
		else if (morse[a] == SEPARATOR && morse[a-1] != FAKE_SPACE) {//get one charactor
			if (true == morse2str(temp, &ch) && b < 5) {
				string[c++] = ch;
			} else if (true == morse2mark(temp, &ch)) {
				string[c++] = ch;
			} else if (true == morse2num(temp, &ch)) {
				string[c++] = ch;
			} else {
			}

			//clean
			b = 0;
			memset(temp->c, '*' ,8);
		} else if (morse[a] == FAKE_SPACE) { //have a space
			string[c++] = ' ';
		}
	} 
}

void str_to_morse_str(char *string ,char *morse, int buf_len) {
	int a = 0;
	int b = 0;
	int len = strlen(string);
	Morse_t * temp = new_morse();

	for (; a < len; a ++ ) {
		if (buf_len < 8 || b >= buf_len) {
			break;
		}

		if (string[a] != ' ') {
			//if is a num 
			if (string[a] >= '0' && string[a] <= '9') {
				if (true == num2morse(string[a], temp)) {
					morse[b++] = temp->c[0];
					morse[b++] = temp->c[1];
					morse[b++] = temp->c[2];
					morse[b++] = temp->c[3];
					morse[b++] = temp->c[4];
				} else {
					return ;
				}
			}
			//if is a character
			else if (string[a] >= 97 && string[a] <= 122) {
				if (true == str2morse(string[a], temp)) {
				morse[b++] = temp->c[0];
				if (temp->c[1] != '*')
					morse[b++] = temp->c[1];
				if (temp->c[2] != '*')
					morse[b++] = temp->c[2];
				if (temp->c[3] != '*')
					morse[b++] = temp->c[3];
				} else {
					return ;
				}
			}
			//if is a mark
			else if (string[a] <= 127) {
				if (true == mark2morse(string[a], temp)) {
				morse[b++] = temp->c[0]; 
				morse[b++] = temp->c[1];
				morse[b++] = temp->c[2];
				morse[b++] = temp->c[3];
				morse[b++] = temp->c[4];
				if (temp->c[5] != '*')
					morse[b++] = temp->c[5];
				if (temp->c[6] != '*')
					morse[b++] = temp->c[6];
				} else {
					return ;
				}
			} else {
				return ;
			}

			//clean
			memset(temp->c, 0 , 8);

			//morse[b++] = SEPARATOR;
		
		} else if (string[a] == ' ') { //have a space and add / to instead
			morse[b++] = FAKE_SPACE;
			morse[b++] = SEPARATOR;
		}
	}

}

void str2lowcase(char *str, char *out, int buf_len) {
	int len = strlen(str);
	int a = 0;

	if (len >= buf_len) {
		printf("buf is too low\n");
		return;
	}

	for (;a < len; a++) {
		if (str[a] >= 'A' && str[a] <= 'Z') {
			out[a] = str[a] + 32;
		} else {
			out[a] = str[a];
		}
	}
}
