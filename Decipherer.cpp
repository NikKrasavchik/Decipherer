#include <iostream>

#include "Hamming.h"
#include "HammingPacket.h"

using namespace std;

// For debug:
// Hamming test input : 001010011110111
// correct result :     001010011010111

int main()
{
	Hamming h;
	cin >> h;
	cout << h << endl;
	HammingPacket f = h.get_packet(0);
	cout << f;
}