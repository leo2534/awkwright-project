#include "C:\Users\PughL14\OneDrive - Hutchesons' Grammar School\ICT\Co-curricular programming\visual studio\projects\arkwright cleanup\src\config.h"

void print(float f){
    std::cout << f << std::endl;
}

void print(std::vector <int> ints){
    for(int i: ints){
        print(i);
    }
}

void print(std::vector <std::string> strings){
    for(std::string str : strings){
        std::cout << str << std::endl;
    }
}

void print(std::vector <float> f){
    for(float i : f){
        std::cout << i << std::endl;
    }
}

void print(int i){
    std::cout << i << std::endl;
}

void print(double d){
    std::cout << d << std::endl;
}

void print(std::string character){
    std::cout << character << std::endl; 
}

void print(std::list <int> ints){
    for(int i :ints){
        std::cout << i << std::endl;
    }
}

void print(std::list <std::string> list){
    for(std::string str : list){
        std::cout << "a" << str << "a" << std::endl;
    }
}

void print(std::list <char> list){
    for(char c : list){
        std::cout << c << std::endl;
    }
}

class Point{
    public:
        float x, y;
    Point(float xCoor=0, float yCoor=0) : x(xCoor), y(yCoor){}
    void setXY(float x, float y){
        this->x = x;
        this->y = y;
    }
        
};

class Instruction{
    public:
        std::vector <Point> numbers;
        char instructionChar;
    Instruction(std::vector <Point> inputNumbers, char inputChar) : numbers(inputNumbers), instructionChar(inputChar){}

    void setNumbersAndPath(std::vector <Point> numbers, char InstructionChar){
        this->numbers = numbers;
        this->instructionChar = instructionChar;
    }
    void setNumbers(std::vector <Point> numbers){
        this->numbers = numbers;
    }

    void setInstructionChar(char instructionChar){
        this->instructionChar = instructionChar;
    }
};

void print(Point p){
    std::cout << p.x << ", " << p.y << std::endl;
}

void print(std::vector <Point> v){
    for(auto p: v){
        print(p);
    }
}

std::list <int> createIndexes(std::string contents, std::string acceptChars, int startOffset=2){
    //std::cout << acceptChars << std::endl;
    std::list <int> commands = {};
    int index = contents.find_first_not_of(acceptChars, startOffset);
    int count = 0;
    int lastLetter = 0;
    while(index != -1 && count < 100){//while loop until cannot find another command
        count++;
        
        commands.push_back(index);
        commands.push_back(index);
        if(lastLetter ==1){
            
            commands.pop_back();
                
        }
        lastLetter = 0;
        
        //std::cout << "index" << std::endl;
        index = contents.find_first_not_of(acceptChars, index+1);
        //std::cout << ":" << contents[index] << ":" << std::endl;
        
        }
    commands.push_front(0);
    if(!lastLetter){
    commands.push_back(contents.length());
    }
    return commands;
}

bool hasNumbers(std::string str){//returns true is any character contains a number else returns false
    bool returnValue = false;
    int length = str.length();
    std::string numbers = "1234567890";
    for(char ch : str){//loop over all characters
        //std::cout << "has numbers" << numbers.find(ch) << std::endl;
        if(numbers.find(ch) < 10){//if the character is not a number
        
            returnValue = true;
        }
    }
    return returnValue;
}

std::string findD(std::string contents){
    int startIndex = contents.find("d=")+3;
    int endIndex = contents.find('"', startIndex + 3);
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

std::list <char> isolateInstructionChar(std::list <std::string> instructionArray){
    std::list <char> instructionChars = {};
        for(std::string instruction : instructionArray){
        char instructionChar = instruction[0];
        instructionChars.push_back(instructionChar);
        }
    return instructionChars;
}

std::list <std::string> isolateInstructions(std::string contents){
    std::list <std::string> finalInstructions;
    const std::string delims(" ,.-1234567890");
    std::list <int> indexes = createIndexes(contents, delims, 0);
    std::list <std::string> instructions = createSubstring(contents, indexes);
    int counter = 0;
    for(std::string instruction : instructions){
        //std::cout << "instruction: " << instruction << std::endl;
        if(counter != 0){
        finalInstructions.push_back(instruction);
        }
        counter++;
    }
    return finalInstructions;
}

std::vector <std::vector <Point>> isolateCoordinates(std::vector <std::string> instructionsWithoutCharacter){
    std::vector <std::vector <Point>> output;
    Point point(0,0);
    for(std::string instruction : instructionsWithoutCharacter){
        //std::cout << "instruction " << std::endl;
        std::list <int> indexes = createIndexes(instruction, "1234567890.", 0);
        std::list <std::string> instructions = createSubstring(instruction, indexes);
        
        std::vector <std::string> vectorInstructions = {};
        for(std::string stringNumber : instructions){
            if(!hasNumbers(stringNumber)){}//if the string is empty ignore it
            else{
                //std::cout << "input number" << stringNumber << std::endl;
                std::string numbers = "1234567890-";
                
                //std::cout << "string number " << std::endl;
                
                while(numbers.find(stringNumber[0]) > 4294967294){//while the first character is not a number
                    //print("while loop 1");
                    stringNumber = stringNumber.substr(1);//remove the first character
                    }
                    /*
                int counter = 0;
                while(!numbers.find(stringNumber[stringNumber.length()-1]) && counter < 100){
                    counter++;
                    prints("while loop");
                    prints(";"+stringNumber + ";");
                    stringNumber = stringNumber.substr(0,stringNumber.length()-2);
                   }*/
                //std::cout << "string number ." << stringNumber << "." << std::endl;
                vectorInstructions.push_back(stringNumber);
                }
            }
        std::vector <Point> dummy = {};
        for(int counter = 0; counter < vectorInstructions.size(); counter = counter + 2){
            //std::cout << "counter" << counter << std::endl;
            float yCoor;
            //std::cout << vectorInstructions[counter] << "/1" << std::endl;
            float xCoor = std::stof(vectorInstructions[counter]);
            if(counter+1 < vectorInstructions.size()){
            //std::cout << vectorInstructions[counter+1] << "/2" << std::endl;
            yCoor = std::stof(vectorInstructions[counter+1]);
            //std::cout << "normakl" << std::endl;
            }
            else{
                //std::cout << "else" << std::endl;
                yCoor = NAN;
                //std::cout << "nan" << std::endl;
            }
            //std::cout << "xcoor" << xCoor << " xcoor" << yCoor <<  " " << counter << " " << vectorInstructions.size() << std::endl;
            point.setXY(xCoor, yCoor);
            dummy.push_back(point);
        }
        output.push_back(dummy);
    
        
        }
    return output;
    }

std::vector <std::string> isolateNumber (std::list <std::string> instructionsWithCharacters){
    std::vector <std::string> output = {};
    std::string stringOfNumbers = "1234567890-";
    for(std::string instruction : instructionsWithCharacters){
        if(hasNumbers(instruction)){
        while (stringOfNumbers.find(instruction[0]) == std::string::npos){
            //prints( "instruction substring " + instruction);
            instruction = instruction.substr(1);
        }
        output.push_back(instruction);
    }
    else{
        std::string NotAnumber = "NaN";
        output.push_back(NotAnumber);
    }
    }
    return output;
}

void moveto(std::ofstream& outputfile, Point & penPointer, std::vector <Point> numbers, char instruction, Point& lastMoveto, std::ofstream& outputSVG){
    //std::cout << "pen pointer" << penPointer.x << " " << penPointer.y << std::endl;
    if(instruction == 'm'){
        outputfile << "IpenupI\n";
        outputfile << "IlinetoI $" << std::to_string(numbers[0].x-penPointer.x) << "$ $" << std::to_string(numbers[0].y-penPointer.y) << "$\n";
        outputfile << "IpendownI\n";
        lastMoveto.setXY(numbers[0].x+penPointer.x,numbers[0].y+penPointer.y);

        outputSVG << numbers[0].x-penPointer.x << " " << numbers[0].y-penPointer.y << " ";
    }
    else{
        outputfile << "IpenupI\n";
        outputfile << "IhomeI\n";
        outputfile << "IlinetoI $" << std::to_string(numbers[0].x-penPointer.x) << "$ $" << std::to_string(numbers[0].y-penPointer.y) << "$\n";
        outputfile << "IpendownI\n\n";
        //std::cout << "moveto" << numbers[0].x << " " << numbers[0].y << std::endl;
        
        outputSVG << numbers[0].x-penPointer.x << " " << numbers[0].y-penPointer.y << " ";
        lastMoveto.setXY(numbers[0].x, numbers[0].y);lastMoveto.setXY(numbers[0].x, numbers[0].y);
    }
    penPointer.setXY(numbers[0].x, numbers[0].y);
}

void lineto(std::ofstream& outputfile, Point& penPointer, std::vector <Point> numbers, char instruction, std::ofstream& outputSVG){
    int scale = 1;
    if(instruction == 'l'){
        //std::cout << numbers[0].x << "lineto before" << numbers[0].y << std::endl;
        //std::cout << numbers[0].x << " lineto " << numbers[0].y << std::endl;
        outputfile << "IlinetoI $" << std::to_string(numbers[0].x*scale) << "$ $" << std::to_string(numbers[0].y*scale) << "$\n";
        
        outputSVG << numbers[0].x*scale << " " << numbers[0].y*scale << "  ";
        
        penPointer.setXY(numbers[0].x+penPointer.x, numbers[0].y+penPointer.y);
        
    }
    else{
        
        outputfile << "IlinetoI $" << std::to_string((numbers[0].x-penPointer.x)*scale) << "$ $" << std::to_string((numbers[0].y-penPointer.y)*scale) << "$\n";
        
        //useful   std::cout << "lineto " << numbers[0].x << " " << numbers[0].y << " penPointer " << penPointer.x <<  " " << penPointer.y << std::endl; 
        outputSVG << (numbers[0].x-penPointer.x)*scale << " " << (numbers[0].y-penPointer.y)*scale << "  ";
        penPointer.setXY(numbers[0].x, numbers[0].y);
        
    }
}

void closePath(std::ofstream& outputFile, Point& penPoint, Point lastMoveto, std::ofstream& outputSVG){
    Point dummyPoint(lastMoveto.x-penPoint.x, lastMoveto.y-penPoint.y);
    std::vector <Point> dummy = {dummyPoint};
    //std::cout << "close path" << lastMoveto.x << " " << lastMoveto.y << " " << penPoint.x << " " << penPoint.y << std::endl;
    //std::cout << dummyPoint.x << " " << dummyPoint.y << std::endl;
    lineto(outputFile, penPoint, dummy, 'l',  outputSVG);
}

Point lerp(Point coord1, Point coord2, float time){
    float x1,y1, x2, y2, tx, ty;
    x1 = coord1.x;
    y1 = coord1.y;
    x2 = coord2.x;
    y2 = coord2.y;
    tx = x2 + (1-time)*(x1-x2);
    ty = y2 + (1-time)*(y1-y2);
    Point lerpPoint(tx,ty);
    return lerpPoint;
}

Point cubicBezierLerp(std::vector <Point> coordinates, double t, Point penPoint){
    Point lerpPointAB = lerp(Point(0,0), coordinates[0], t);
    Point lerpPointBC = lerp(coordinates[0], coordinates[1], t);
    Point lerpPointCD = lerp(coordinates[1], coordinates[2], t);
    Point lerpPointAB2BC = lerp(lerpPointAB, lerpPointBC, t);
    Point lerpPointBC2CD = lerp(lerpPointBC, lerpPointCD, t);
    Point lerpPoint = lerp(lerpPointAB2BC, lerpPointBC2CD, t);
    return lerpPoint;
}

void cubicBezier(std::ofstream& outputFile, Point& penPoint, std::vector <Point> coordinates, char instructionCharacter, std::ofstream& outputSVG){
    
    Point lastLerpPoint(0,0);
    Point lerpPoint(0,0);
    if (instructionCharacter == 'c'){
        
        //has to be double to return a double for time after division otherwise int/int = int allways
        double n = 10;//number of segments
        //have to use integer iterator for loop then divide by n as floats in loops cause issues
        for(int i = 0; i <= n; i=i+1){
            double t = i/n;
            lastLerpPoint = lerpPoint;
            //get where the bezier is at the value of time
            lerpPoint = cubicBezierLerp(coordinates, t, penPoint);
            outputSVG << "l" << " ";      /*has to take away last point as all the lerp points are relative to the start i think*/
            lineto(outputFile, penPoint, {Point(lerpPoint.x-lastLerpPoint.x, lerpPoint.y-lastLerpPoint.y)}, 'l', outputSVG);
        }
    }
    //if the instruction is absolute then convert the cordinates to relative
    else{
        std::vector <Point> relativeCoordinates = {};
        for (Point point : coordinates){
            relativeCoordinates.push_back(Point(point.x-penPoint.x, point.y-penPoint.y));
        }
        cubicBezier(outputFile, penPoint, relativeCoordinates, 'c', outputSVG);
    }
}

void writeInstructions(Instruction instructions, std::ofstream& outputFile, Point& penPoint, Point& lastMoveto, std::ofstream& outputSVG){
    
    char instructionCharacter = instructions.instructionChar;
    if(instructionCharacter == 'l' || instructionCharacter == 'L'){
        outputSVG << 'l' << " ";

        lineto(outputFile, penPoint, instructions.numbers, instructions.instructionChar,  outputSVG);

        //std::cout << penPoint.x << "penPointer" << penPoint.y << std::endl;
    }
    else if(instructionCharacter == 'V' || instructionCharacter == 'v'){
        if(instructionCharacter == 'V'){
            outputSVG << 'l' << " ";

            Point dummyPoint(penPoint.x, instructions.numbers[0].x);
            std::vector <Point> dummy = {dummyPoint};
            lineto(outputFile, penPoint, dummy, 'L',  outputSVG);
        }
        else{
            outputSVG << 'l' << " ";

            Point dummyPoint(0, instructions.numbers[0].x);
            std::vector <Point> dummy = {dummyPoint};
            lineto(outputFile, penPoint, dummy, 'l',  outputSVG);
        }
        //std::cout << penPoint.x << "penPointer" << penPoint.y << std::endl;
    }
    else if(instructionCharacter == 'H' || instructionCharacter == 'h'){
        if(instructionCharacter == 'h'){
            outputSVG << 'l' << " ";

            Point dummyPoint( instructions.numbers[0].x, 0);
            std::vector <Point> dummy = {dummyPoint};
            lineto(outputFile, penPoint, dummy, 'l',  outputSVG);
        }
        else{
            outputSVG << 'l' << " ";

            Point dummyPoint(instructions.numbers[0].x, penPoint.y);
            std::vector <Point> dummy = {dummyPoint};
            lineto(outputFile, penPoint, dummy, 'L',  outputSVG);
        }
        //std::cout << penPoint.x << "penPointer" << penPoint.y << std::endl;
    }
    else if(instructionCharacter == 'C' || instructionCharacter == 'c'){
        cubicBezier(outputFile, penPoint, instructions.numbers, instructions.instructionChar,  outputSVG);
        //std::cout << penPoint.x << "penPointer cubic bezier" << penPoint.y << std::endl;
    }
    else if(instructionCharacter == 'M' || instructionCharacter == 'm'){
        outputSVG << 'm' << " ";


        moveto(outputFile, penPoint, instructions.numbers, instructions.instructionChar, lastMoveto,  outputSVG);
        //std::cout << penPoint.x << "penPointer" << penPoint.y << std::endl;
        //std::cout << lastMoveto.x << "last moveto" << lastMoveto.y << std::endl;
    }
    else if(instructionCharacter == 'Z' || instructionCharacter == 'z'){
        outputSVG << 'l' << " ";
        //std::cout << lastMoveto.x << "last moveto z" << lastMoveto.y << std::endl;
        closePath(outputFile, penPoint, lastMoveto,  outputSVG);
        //std::cout << penPoint.x << "penPointer" << penPoint.y << std::endl;
    }
    else {
        std::cout << "warning: instruction " << instructionCharacter << "not supported" << std::endl;
    }
    //std::cout << std::endl;
}

void onFindPath(std::string contents, std::ofstream& outputFile, Point& penPointer, std::ofstream& outputSVG){
    //output boilerplate to the svg
    outputSVG << "<path d=" << '"';

    //variable declarations
    Point lastMoveto(0,0);
    std::vector <Point> dummy;
    

    dummy.push_back(Point(0,0));
    Instruction instruction(dummy, 'A');

    std::vector <std::vector <Instruction>> twodArrayOfCoordinates = {};
    

    contents = findD(contents);
    
    std::list <std::string> instructionsWithCharacter = isolateInstructions(contents);
    
    std::list <char> instructionCharacters = isolateInstructionChar(instructionsWithCharacter);
    
    std::vector <std::string> instructions = isolateNumber(instructionsWithCharacter);
    
    
    std::vector <std::vector <Point>> coordinates = isolateCoordinates(instructions);
    std::vector <Instruction> dummyVector = {};
    int counter = 0;
    for(char character: instructionCharacters){
        
        dummyVector.push_back(Instruction(coordinates[counter], character));
        counter++;
        }
    
    
    twodArrayOfCoordinates.push_back(dummyVector);
    
    for(std::vector <Instruction> vectorOfInstructions : twodArrayOfCoordinates){        
        for (Instruction instructionsFromVector : vectorOfInstructions){
            writeInstructions(instructionsFromVector, outputFile, penPointer, lastMoveto, outputSVG);
        }
    }

    //more svg boilerplate
    outputSVG << '"' << " style=" << '"' << "fill:none;stroke:blue;stroke-width:1" <<  '"' << "/>" << "\n";
}

void approximateEllipse(std::ofstream& outputFile, Point& penPointer, std::vector <float> arrayOfNumbers, std::ofstream& outputSVG){
    std::vector <Point> coordinates = {};
    int n = 50;//number of segments
    for(int i = 0; i <= n; i=i+1){
        double t = i/n;
    }
}

void onFindEllipse(std::string contents, std::ofstream& outputFile, Point& penPointer, std::ofstream& outputSVG){
    print("found ellipse");
    std::vector <int> indexes;
    int currentIndex = 0;
    int repetitions = 0;
    while (contents.find('"', currentIndex)<contents.length() && repetitions < 100){
        repetitions++;
        int nextIndex = contents.find('"', currentIndex);
        indexes.push_back(nextIndex);
        currentIndex = nextIndex + 1;
    }
    repetitions = 0;
    std::vector <float> arrayOfNumbers; 
    while (repetitions < indexes.size()){
        arrayOfNumbers.push_back(std::stof(contents.substr(indexes[repetitions]+1, indexes[repetitions+1]-indexes[repetitions]-1)));
        repetitions = repetitions + 2;
    }
    approximateEllipse(outputFile, penPointer, arrayOfNumbers, outputSVG);
    print(arrayOfNumbers);
    
    print(contents);
    print("end of ellipse");

}

int main(){
    Point penPointer(0,0);
    std::string contents;
    
    std::ifstream file("C:/Users/PughL14/OneDrive - Hutchesons' Grammar School/ICT/Co-curricular programming/visual studio/projects/arkwright cleanup/files/hearts.svg");//files/mySVG.svg
    if (!file.is_open()) {
        std::cout << "Unable to open file\n";
        std::cin >> contents;
    return -1;

    }
    else{
    
        std::cout << "File opened successfully\n";
    }
    std::ofstream outputFile ("files/output.stc");
    if(!outputFile.is_open()){
        std::cout << "unable to open output file" << std::endl;
    }
    else{
        outputFile << "IhomeI\n";
        std::cout << "opened output file successfully" << std::endl;
    }

    std::ofstream outputsvg ("C:/Users/PughL14/OneDrive - Hutchesons' Grammar School/ICT/Co-curricular programming/visual studio/projects/arkwright cleanup/files/output.svg");
    if(!outputsvg.is_open()){
        std::cout << "unable to open output file" << std::endl;
    }
    else{
        outputsvg << "<?xml version=" << '"' << "1.0" << '"' <<  " encoding=" << '"' << "utf-8" << '"' << "?>" << "\n";
        outputsvg << "<svg width=" << '"' << "2000px" << '"' << " height=" << '"' << "2000px" << '"' << " viewBox=" << '"' << "0 0 2000 2000" << '"' << " xmlns=" << '"' << "http://www.w3.org/2000/svg" << '"' << ">" << "\n";
        std::cout << "succesfully opened output svg" << std::endl;
    }
    std::vector <std::vector <Instruction>> twodArrayOfCoordinates = {};
    while(getline(file, contents)){
        //print("running");
        if(contents.find("<path") != std::string::npos){
            onFindPath(contents, outputFile, penPointer, outputsvg);
        }
        else if(contents.find("<ellipse") != std::string::npos){
            onFindEllipse(contents, outputFile, penPointer, outputsvg);
        }
        //test if the line is a tag and that it isnt svg boilerplate tags
        else if(contents.find("<") != std::string::npos && contents.find("<svg") == std::string::npos && contents.find("</svg") == std::string::npos && contents.find("<?xml") == std::string::npos){
            print("unrecognised tag");
            print(contents);
        }
    
    }
    outputsvg << "</svg>" << "\n";
    outputsvg.close();
    outputFile.close();
    file.close();
}