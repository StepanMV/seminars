import <iostream>;
import CppMisc;

int main()
{
    const size_t len = 10000000;
    Timer timer1, timer2, timer3, timer4, timer5;

    int* array1 = ArraysMisc::randomArray<int>(len);
    int* array2 = ArraysMisc::randomArray<int>(len);
    int* array3 = ArraysMisc::randomArray<int>(len);
    int* array4 = ArraysMisc::randomArray<int>(len);
    int* array5 = ArraysMisc::randomArray<int>(len);

    //ArraysMisc::printArray<int>(array1, len);
    //ArraysMisc::printArray<int>(array2, len);
    //ArraysMisc::printArray<int>(array3, len);
    //ArraysMisc::printArray<int>(array4, len);
    //ArraysMisc::printArray<int>(array5, len);
    std::cout << std::endl;

    timer1.start();
    //ArraySorts::bubbleSort<int>(array1, len);
    timer1.end();

    timer2.start();
    //ArraySorts::insertionSort<int>(array2, len);
    timer2.end();

    timer3.start();
    //ArraySorts::selectionSort<int>(array3, len);
    timer3.end();

    timer4.start();
    ArraySorts::mergeSort<int>(array4, 0, len - 1);
    timer4.end();

    timer5.start();
    ArraySorts::quickSort<int>(array5, 0, len - 1);
    timer5.end();


    //ArraysMisc::printArray<int>(array1, len);
    //ArraysMisc::printArray<int>(array2, len);
    //ArraysMisc::printArray<int>(array3, len);
    //ArraysMisc::printArray<int>(array4, len);
    //ArraysMisc::printArray<int>(array5, len);

    std::cout << std::endl;
    std::cout << "BubbleSort: " << timer1.getResult() / 1000000 << " ms\n";
    std::cout << "InsertionSort: " << timer2.getResult() / 1000000 << " ms\n";
    std::cout << "SelectionSort: " << timer3.getResult() / 1000000 << " ms\n";
    std::cout << "MergeSort: " << timer4.getResult() / 1000000 << " ms\n";
    std::cout << "QuickSort: " << timer5.getResult() / 1000000 << " ms\n";
    return 0;
}
