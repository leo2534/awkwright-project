#include "config.h"

class Point{
    public:
        float x, y;
    
    void setXY(float x, float y){
        this->x = x;
        this->y = y;
    }
        
};

std::list <int> createIndexes(std::string contents, std::string acceptChars, int startOffset=2){
    //std::cout << acceptChars << std::endl;
    std::list <int> commands = {};
    int index = contents.find_first_not_of(acceptChars, startOffset);
    int count = 0;
    int lastLetter = 0;
    while(index != -1 && count < 100){//while loop until cannot find another command
        count++;
        if (contents[index] == 'Z' || contents[index] == 'z'){//make index negative if the letter is Z or z
            //std::cout << index << "z " << std::endl;
            commands.push_back(index);
            commands.push_back(index);
            commands.push_back(index+1);
            lastLetter = 1;
        }
        else{
            //std::cout << index << std::endl;
            commands.push_back(index);
            commands.push_back(index);
            if(lastLetter ==1){
            
                commands.pop_back();
                
            }
            lastLetter = 0;
        }
        //std::cout << "index" << std::endl;
        index = contents.find_first_not_of(acceptChars, index+1);
        }
    commands.push_front(0);
    if(!lastLetter){
    commands.push_back(contents.length());
    }
    return commands;
}

std::string findD(std::string contents){
    int startIndex = contents.find("d=")+3;
    int endIndex = contents.find("/", startIndex + 3);
    return contents.substr(startIndex, endIndex-startIndex);
}

std::list <std::string> createSubstring(std::string contents, std::list <int> indexes){
    for(int i:indexes){
        //std::cout << i << " ";
    } 
    int lastIndex = 0;
    std::string instruction = "";
    std::list <std::string> subStrings;
    std::string substring;
    int it = 0;
    for(int index : indexes){
        it++;
        if(it%2==0){
            substring = contents.substr(lastIndex, index-lastIndex);
            subStrings.push_back(substring);
        }
        lastIndex = index;
    }
    return subStrings;
}

std::list <std::string> all(std::string path){
    std::string contents = findD(path);
    std::cout << "contents: " << contents << std::endl;
    std::list <int> indexes = createIndexes(contents, "0123456789,.- ");
    //for(int i : indexes){
    //    std::cout << "index" << i << "  ";
    //}
    return createSubstring(contents, indexes);
    }  

std::list <char> isolateInstructionChar(std::list <std::string> instructionArray){
    std::list <char> instructionChars = {};
        for(std::string instruction : instructionArray){
        char instructionChar = instruction[0];
        instructionChars.push_back(instructionChar);
        }
    return instructionChars;
}

std::vector <std::string> isolateNumber (std::string contents, std::string acceptChars){
    std::vector <std::vector <float>> output = {};
    std::vector <std::string> dummy = {};
    //generate individual strings of instructions
    std::list <int> indexes = createIndexes(contents, acceptChars);
    std::list <std::string> strings = createSubstring(contents, indexes);
    //remove spaces and letter
    for(std::string numberStrings:strings){
        numberStrings.erase(std::remove_if(numberStrings.begin(), numberStrings.end(), ::isspace), numberStrings.end());
        numberStrings = numberStrings.substr(1);
        dummy.push_back(numberStrings);
    }
    return dummy;
    
}
/*for(auto v:output){
        std::cout << "instructriopn" << v << std::endl;
        std::list <int> index = createIndexes(v, "1234567890.", 1);
        //for(int i:index){
        //    std::cout << "indexes" << i << std::endl;
        //}
        
        std::list <std::string> strings = createSubstring(v, index);
        
        for(std::string numberString: strings){
            //std::cout << "number string start loop :" << numberString << ":" << std::endl;

            
            numberString.erase(std::remove_if(numberString.begin(), numberString.end(), ::isspace), numberString.end());
            float number;
            if(numberString.empty()){
                std::cout << "empty number string" << numberString << std::endl;
                number = NAN;
            }
            else{
                if(numberString[0] == '-' || numberString[0] ==',' || numberString[0] == ' '){
                numberString = numberString.substr(1);
            }
                
                number = std::stof(numberString);*/

std::vector <std::vector <float>> isolateNumbersFromString(std::list <std::string> pathStrings, std::string acceptChars){
    //declare variables
    std::string zeroToNineNumbers = "1234567890";
    std::vector <std::vector <float>> outputFloat2DArray = {};
    std::vector <float> dummyStringArray;
    //loop through all paths
    for(std::string singlePathString: pathStrings){
        //clear dummy array
        dummyStringArray = {};
        //generate array of strings of instructions eg "M 2.2,5.5"
        std::list <int> pathInstructionsIndex = createIndexes(singlePathString, acceptChars);
        std::list <std::string> instructionsStrings = createSubstring(singlePathString, pathInstructionsIndex);
        //loop through individual instrucrutions strings
        for(std::string singleInstructionString: instructionsStrings){
            //clean up string
            //remove starting letter eg. "2.2,5.5" removed "M "
            while(!zeroToNineNumbers.find(singleInstructionString[0])){
                singleInstructionString = singleInstructionString.substr(1);
            }
                //generate strings of number instructions eg. "2.2", ",5.5"
                std::list <int> numberSeparatorIndexes = createIndexes(singleInstructionString, "1234567890.", 0);
                std::list <std::string> individualInstructionsStrings = createSubstring(singleInstructionString, numberSeparatorIndexes);
                //loop through instruction strings
                for(std::string individualInstructionString: individualInstructionsStrings){
                    //remove spaces from string
                    individualInstructionString.erase(std::remove_if(individualInstructionString.begin(), individualInstructionString.end(), ::isspace), individualInstructionString.end());
                    float outputNumber;
                    if(individualInstructionString.empty()){
                        outputNumber = NAN;
                    }
                    else{
                        outputNumber = std::stof(individualInstructionString);
                    }
                    dummyStringArray.push_back(outputNumber);
                }
            
        }
        outputFloat2DArray.push_back(dummyStringArray);
    }
    return outputFloat2DArray;
}

void moveto(std::ofstream& outputfile, Point & penPointer, std::vector <float> numbers, char instruction){
    if(instruction == 'm'){
        outputfile << "IpenupI\n";
        outputfile << "IlinetoI $" << std::to_string(numbers[0]) << "$ $" << std::to_string(numbers[1]) << "$\n";
        outputfile << "IpendownI\n";
    }
    else{
        outputfile << "IpenupI\n";
        outputfile << "IhomeI\n";
        outputfile << "IlinetoI $" << std::to_string(numbers[0]) << "$ $" << std::to_string(numbers[1]) << "$\n";
        outputfile << "IpendownI\n\n";
    }
    penPointer.setXY(numbers[0], numbers[1]);
}

void lineto(std::ofstream& outputfile, Point& penPointer, std::vector <float> numbers, char instruction){
    if(instruction == 'l'){
        outputfile << "IlinetoI $" << std::to_string(numbers[0]) << "$ $" << std::to_string(numbers[1]) << "$\n";
    }
    else{
        std::cout << "uppercase" << std::endl;
        outputfile << "IlinetoI $" << std::to_string(numbers[0]-penPointer.x) << "$ $" << std::to_string(numbers[1]-penPointer.y) << "$\n";
    }
    penPointer.setXY(numbers[0], numbers[1]);
}

void endOfPath(std::ofstream& outputfile, char instruction){
    if(instruction == 'z'){
        outputfile << "Iend of pathI\n";
    }
    else{
        outputfile << "Iend of pathI\n";
    }
}

void callInstructions(std::list <std::string> instructions, std::list <char> instructionChars){
    std::ofstream outputfile("files/output.stc");
    Point penPointer;
    penPointer.setXY(0,0);
    std::vector <std::vector<float>> floatNumberInstructions = isolateNumbersFromString(instructions, "123456789.");
    int count = -1;
    for(char instructionCharacter: instructionChars){
        count++;
        if(instructionCharacter == 'M' || instructionCharacter == 'm'){
            moveto(outputfile, penPointer, floatNumberInstructions[count], instructionCharacter);
        }
        else if(instructionCharacter == 'H' || instructionCharacter == 'h'){
            float x = 0;
            char instructionchar = 'l';
            if(instructionCharacter == 'H'){instructionchar = 'L';}
            lineto(outputfile, penPointer, {x, floatNumberInstructions[count][0]}, instructionchar);
        }
        else if(instructionCharacter == 'V' || instructionCharacter == 'v'){
            float y = 0.0;
            char instructionchar = 'l';
            if(instructionCharacter == 'V'){instructionchar = 'L';}
            if(floatNumberInstructions[count].size() != 1){std::cout << "more than one element following vertical line instruction" << std::endl;}
            lineto(outputfile, penPointer, {floatNumberInstructions[count][0], y}, instructionchar);
        }
        else if(instructionCharacter == 'L' || instructionCharacter == 'l'){
            lineto(outputfile, penPointer, floatNumberInstructions[count], instructionCharacter);
        }
        else if(instructionCharacter == 'C' || instructionCharacter == 'c'){
            std::cout << "unhandled path type cubic bezier" << std::endl;
        }
        else if(instructionCharacter == 'Z' || instructionCharacter == 'z'){
            endOfPath(outputfile, instructionCharacter);
        }
        else{std::cout << "unhandled path type " << instructionCharacter<< std::endl;}
    }
    outputfile.close();
}

int main(){
    /*
    std::list <int> result = createIndexes("M 2,2 L 8,2L 8,8 L 2,8 L 2,2 Z M 7,3 L 3 3 L 3,7 L 7,7 L 7,3 Z", "123456789.,- ");
    std::list <int> correctResult = {0, 5, 6, 11, 12, 17, 18, 23, 24, 29, 30, 31};
    std::cout << "result: " << std::endl;
    int count = 0;
    for(int i : result){
        count ++;
        if(count % 2==0){
            std::cout << i << " ";
        }
        else{
        std::cout << i << "-";
        }
    }
    /**/
    /*
    std::string result = findD("path class=cls-2 d=/M196.37,122c-65.37-46-122.37,96-22.37,213,54.56,63.83,238.82,137.64,243,137/fthjtgfbdbhgtjl");
    std::string correctResult = "M196.37,122c-65.37-46-122.37,96-22.37,213,54.56,63.83,238.82,137.64,243,137";
    std::cout << "result:         " << result << " \ncorrect result: " << correctResult <<  std::endl;
    /**/  
    /*
    std::list <std::string> result = createSubstring("M196.37,122c-65.37-46-122.37,96-22.37,213,54.56,63.83,238.82,137.64,243,137", {0, 11, 11, 75});//0, 5, 6, 11, 12, 17, 18, 23, 24, 29, 30, 31
    std::list <std::string> correctResult = {"M 2,2", "L 8,2", "L 8,8", "L 2,8", "L 2,2", "Z"};
    for(std::string i : result){
        std::cout << i << ": :";
    }
    /**/
    /*
    std::list <std::string> result = all("path class=/cls-2/ d=/M196.37,122c-65.37-46-122.37,96-22.37,213,54.56,63.83,238.82,137.64,243,137/safvnbdfbsb>");
    std::list <std::string> correctResult = {"M196.37,122", "c-65.37-46-122.37,96-22.37,213,54.56,63.83,238.82,137.64,243,137", "Z"};
    std::cout << "\n";
    for(std::string i : result){
        std::cout << i << ": :";
    }
    if(result == correctResult){
        std::cout << "\ncorrect result" << std::endl;
    }
    else{
        std::cout << "\ntest failed" << std::endl;
    }
    
    std::cout << "next test" << std::endl << std::endl << std::endl;
    result = all("path fill-rule=even-odd clip-rule=even-odd d=/M2,2L8,2L8,8L2,8L2,2   ZM7,3L 3 3 L 3,7 L 7,7 L 7,3 Z/ fill=#ff00ffgdfhgjkgjl");
    correctResult = {"M 2,2 ", "L 8,2 ", "L 8,8 ", "L 2,8 ", "L 2,2 ", "Z", "M 7,3 ", "L 3,3 ", "L 3,7 ", "L 7,7 ", "L 7,3 ", "Z"};
    std::cout << "\n";
    for(std::string i : result){
        std::cout << i << ": :";
    }
    /**/    
    /*
    std::list <char> result = isolateInstructionChar({"M2,2","L8,2","L8,8","L2,8","L2,2", "Z"});
    std::list <char> correctResult = {'M','L','L','L','L','Z'};
    for(char i:result){
        std::cout << i<< std::endl;
    }
    /**/
    /*
    std::vector <std::vector<float>> result = isolateNumbersFromString({"   M   2.654,2.243      ","L8,2","L8,8","L2,8","L2,2 ", "Z"}, "123456789.");
    std::vector <std::vector<float>> correctResult;
    /**/
    //*
    //callInstructions();
    /**/
    /*
    int result;
    int correctResult;
    if(result == correctResult){
        std::cout << "\ncorrect result" << std::endl;
    }
    else{
        std::cout << "\ntest failed" << std::endl;
    }

    for(auto v: result){
        for(float n : v){
            std::cout << n << std::endl;
        }
    }
    /**/
    /*std::vector <std::string> output = isolateNumber("M 2,2 L 8,2 L 8,8 L 2-8 L 2-2 Z M 7-3 L 3,3 L 3,7 L 7,7 L 7-3 Z", "0123456789.,- ");
    for(auto v:output){
        std::cout << "instructriopn" << v << std::endl;
        std::list <int> index = createIndexes(v, "1234567890.", 1);
        //for(int i:index){
        //    std::cout << "indexes" << i << std::endl;
        //}
        
        std::list <std::string> strings = createSubstring(v, index);
        
        for(std::string numberString: strings){
            //std::cout << "number string start loop :" << numberString << ":" << std::endl;

            
            numberString.erase(std::remove_if(numberString.begin(), numberString.end(), ::isspace), numberString.end());
            float number;
            if(numberString.empty()){
                std::cout << "empty number string" << numberString << std::endl;
                number = NAN;
            }
            else{
                if(numberString[0] == '-' || numberString[0] ==',' || numberString[0] == ' '){
                numberString = numberString.substr(1);
            }
                
                number = std::stof(numberString);
            }
            //std::cout << "dummy :" << number << ":" << std::endl;
            
        }

    }
    /**/
    /*
    std::list <int> indexes = createIndexes("M 2 2 L 8 2 L 8 8 L 2 8 L 2 2 Z M 7 3 L 3 3 L 3 7 L 7 7 L 7 3 Z", "0123456789. ");
    std::list <std::string> strings = createSubstring("M 2 2 L 8 2 L 8 8 L 2 8 L 2 2 Z M 7 3 L 3 3 L 3 7 L 7 7 L 7 3 Z", indexes);
    for(int i:indexes){
        std::cout << "test " << i << std::endl;
    }
    for(std::string s:strings){
        std::cout << "test strings :" << s << ":" << std::endl;
    }/**/
    std::list <std::string> inputStrings = {"M 2,2 L 8,2 L 8,8 L 2-8 L 2-2 Z M 7-3 L 3,3 L 3,7 L 7,7 L 7-3 Z"};
    std::vector <std::vector <float>> result = isolateNumbersFromString(inputStrings, "1234567890,.- ");
    for(std::vector <float> v: result){
        for(float n: v){
            std::cout << "output :" << n << std::endl;
        }
    }
    return 0;
}
