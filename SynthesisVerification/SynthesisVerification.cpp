// SynthesisVerification.cpp : main project file.

#include "stdafx.h"
#include <math.h>
#include <string>
#include <iostream>
using namespace System;
using namespace System::IO;
using namespace std;


inline unsigned flip ( unsigned target, unsigned value){  return target ^ value;}
#define check_bit(ctrl,value) ((ctrl & value) == ctrl)
/*
value  1101 1101
target 0100 0010
value ^= target 

ctrl 1101 write here: If bits 0,2,3 are one in the output, then flip bit 1
	 1111   This will flip bit 1
	 1011   This will not flip bit 1
	 1101   THis will flip bit 1

ctrl 1010
targ 0100
	 1110	This will flip the target bit 2
	 1010   This will flip bit 2
	 0111	This will NOT flip bit 2
	 1011	This will flipt bit 2
*/ 

int main(array<System::String ^> ^args)
{
	//extension name *.qsy
	int quantomCost;
	String ^line;
	int *input, *output, *Control, *Target;

	Control = new int[100];
	Target = new int[100];
	int c_Length = 0, nTerms = 0;
	StreamReader ^file = gcnew StreamReader("0.txt");
	line = file->ReadLine(); 
	line = file->ReadLine();
	quantomCost = System::Convert::ToInt32(line);
	input = new int(0);
	output = new int(0);
	file->ReadLine();
	line = file->ReadLine();
	array<String^>^ list = line->Split(',');
	for(int i=0;i<list->Length-1;i++)
	{
		input[i] = Convert::ToInt32(list[i]);
		nTerms++;
	}

	int bits = (int)(log10((float)nTerms)/log10(2.0));
	c_Length = 0;
	line = file->ReadLine();
	line = file->ReadLine();
	list = line->Split(',');
	for(int i=0;i<list->Length-1;i++)
		output[i] = Convert::ToInt32(list[i]);
	line = file->ReadLine();
	line=file->ReadLine();
	list = line->Split(',');
	for(int i=0;i<list->Length-1;i++)
	{
		Control[i] = Convert::ToInt32(list[i]);
		c_Length++;
	}
	line = file->ReadLine();
	line = file->ReadLine();
	list = line->Split(',');
	for(int i=0;i<list->Length-1;i++)
		Target[i] = Convert::ToInt32(list[i]);

	Console::Write("Control:");
	for(int i=0;i<c_Length;i++)
		Console::Write(Control[i] + " ");
	Console::WriteLine();
	Console::Write("Target: ");
	for(int i=0;i<c_Length;i++)
		Console::Write(Target[i] + " ");

	file->Close();
	
	Console::WriteLine();
	for(int i=0;i<nTerms;i++)
	{
		int v1 = input[i];
		int v2 = output[i];
		Console::Write("v2="+ v2 + " v1=" + v1 + " ");
		for(int j=c_Length-1;j>=0;j--)
		{
			if(check_bit(Control[j],v1)) 
				v1 = flip(Target[j],v1);
			Console::Write(v1 + " ");
		}
		Console::WriteLine();
		if(v1==v2) Console::WriteLine("true"); else Console::WriteLine("false");
	}
	
    String ^anything = Console::ReadLine();
    return 0;
}

