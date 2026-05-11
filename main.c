/*
 * Программа демонстрации алгоритмов сортировки
 * Автор: Elisey P
 * Версия: 1.0
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <limits.h>
#include <string.h>

void printArray(int arr[], int n, const char* message) {
    printf("%s: ", message);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * Сортировка вставками
 * @param arr - массив для сортировки
 * @param n - размер массива
 */
void insertionSort(int arr[], int n) {
    if (arr == NULL || n <= 0) return; // Проверка на NULL
    printf("\n========== SORTIROVKA VSTAVKAMI ==========\n");
    printArray(arr, n, "Nachalnyj massiv");
    printf("([elementy] - otsortirovannaya chast)\n\n");

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        printf("Shag %d: vstavlyaem %d\n", i, key);

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            
            // Промежуточный вывод после перемещения
            printf("         Sdvig: ");
            for (int k = 0; k < n; k++) {
                if (k <= i) {
                    printf("[%d] ", arr[k]);
                } else {
                    printf("%d ", arr[k]);
                }
            }
            printf("\n");
        }
        arr[j + 1] = key;
        
        // Выделяем отсортированную часть [0...i]
        printf("         Final: ");
        for (int k = 0; k < n; k++) {
            if (k <= i) {
                printf("[%d] ", arr[k]);
            } else {
                printf("%d ", arr[k]);
            }
        }
        printf("\n\n");
    }

    printArray(arr, n, "FINAL");
}

// 2. Сортировка выбором
void selectionSort(int arr[], int n) {
    printf("\n========== SORTIROVKA VYBOROM ==========\n");
    printArray(arr, n, "Nachalnyj massiv");
    printf("([elementy] - otsortirovannaya chast)\n\n");

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;

        // Ищем минимум
        printf("Shag %d: ishchem minimum v diapazone [%d...%d]\n", i + 1, i, n - 1);
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        
        printf("         Najden minimum: %d (pozitsiya %d)\n", arr[minIdx], minIdx);

        // Обмен
        if (minIdx != i) {
            printf("         Obmen: arr[%d]=%d <-> arr[%d]=%d\n", i, arr[i], minIdx, arr[minIdx]);
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            
            // Промежуточный вывод после обмена
            printf("         Posle: ");
            for (int k = 0; k < n; k++) {
                if (k <= i) {
                    printf("[%d] ", arr[k]);
                } else {
                    printf("%d ", arr[k]);
                }
            }
            printf("\n");
        } else {
            printf("         Element uzhe na meste\n");
        }
        
        // Выделяем отсортированную часть [0...i]
        printf("         ");
        for (int k = 0; k < n; k++) {
            if (k <= i) {
                printf("[%d] ", arr[k]);
            } else {
                printf("%d ", arr[k]);
            }
        }
        printf("\n\n");
    }

    printArray(arr, n, "FINAL");
}

// 3. Пузырьковая сортировка с флагом
void bubbleSort(int arr[], int n) {
    printf("\n========== PUZYRYKOVAYA SORTIROVKA (s flagom) ==========\n");
    printArray(arr, n, "Nachalnyj massiv");
    printf("([elementy] - otsortirovannaya chast)\n\n");

    int swapped;
    int pass = 1;
    int lastSwapPos = n - 1; // Позиция последнего обмена

    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        int currentLastSwap = 0;
        
        printf("Prokhod %d:\n", pass++);

        for (int j = 0; j < lastSwapPos; j++) {
            if (arr[j] > arr[j + 1]) {
                printf("  Obmen: arr[%d]=%d <-> arr[%d]=%d\n", j, arr[j], j + 1, arr[j + 1]);
                // Обмен
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
                currentLastSwap = j; // Запоминаем позицию последнего обмена
                
                // Промежуточный вывод после обмена
                printf("         ");
                for (int k = 0; k < n; k++) {
                    if (k > lastSwapPos) {
                        printf("[%d] ", arr[k]);
                    } else {
                        printf("%d ", arr[k]);
                    }
                }
                printf("\n");
            }
        }
        
        // Обновляем границу: всё после lastSwapPos уже отсортировано
        if (swapped) {
            lastSwapPos = currentLastSwap;
        }
        
        // Выделяем отсортированную правую часть (всё после lastSwapPos)
        printf("  Final: ");
        for (int k = 0; k < n; k++) {
            if (k > lastSwapPos) {
                printf("[%d] ", arr[k]);
            } else {
                printf("%d ", arr[k]);
            }
        }
        printf("\n\n");

        // Если не было обменов - массив отсортирован
        if (!swapped) {
            printf("Obmenov net - massiv otsortirovan!\n\n");
            break;
        }
    }

    printArray(arr, n, "FINAL");
}

// 5. Шейкерная сортировка
void shakerSort(int arr[], int n) {
    printf("\n========== SHEJKERNAYA SORTIROVKA ==========\n");
    printArray(arr, n, "Nachalnyj massiv");
    printf("([elementy] - otsortirovannaya chast)\n\n");

    int left = -1;  // Граница слева (всё что <= left отсортировано)
    int right = n;  // Граница справа (всё что >= right отсортировано)
    int swapped;
    int pass = 1;

    do {
        swapped = 0;
        int lastSwapRight = left; // Последний обмен при проходе вправо

        // Проход вправо
        printf("Prokhod %d (vpravo):\n", pass);
        for (int i = left + 1; i < right - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                printf("  Obmen: arr[%d]=%d <-> arr[%d]=%d\n", i, arr[i], i + 1, arr[i + 1]);
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
                lastSwapRight = i; // Запоминаем позицию последнего обмена
                
                // Промежуточный вывод после обмена
                printf("         ");
                for (int k = 0; k < n; k++) {
                    if (k <= left || k >= right) {
                        printf("[%d] ", arr[k]);
                    } else {
                        printf("%d ", arr[k]);
                    }
                }
                printf("\n");
            }
        }
        
        // Всё после lastSwapRight+1 уже отсортировано
        right = lastSwapRight + 1;
        
        // Выводим финальное состояние прохода
        printf("  Final: ");
        for (int k = 0; k < n; k++) {
            if (k <= left || k >= right) {
                printf("[%d] ", arr[k]);
            } else {
                printf("%d ", arr[k]);
            }
        }
        printf("\n\n");

        if (!swapped) break;

        swapped = 0;
        int lastSwapLeft = right; // Последний обмен при проходе влево

        // Проход влево
        printf("Prokhod %d (vlevo):\n", pass);
        for (int i = right - 2; i > left; i--) {
            if (arr[i] > arr[i + 1]) {
                printf("  Obmen: arr[%d]=%d <-> arr[%d]=%d\n", i, arr[i], i + 1, arr[i + 1]);
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
                lastSwapLeft = i; // Запоминаем позицию последнего обмена
                
                // Промежуточный вывод после обмена
                printf("         ");
                for (int k = 0; k < n; k++) {
                    if (k <= left || k >= right) {
                        printf("[%d] ", arr[k]);
                    } else {
                        printf("%d ", arr[k]);
                    }
                }
                printf("\n");
            }
        }
        
        // Всё до lastSwapLeft уже отсортировано
        left = lastSwapLeft;
        
        // Выводим финальное состояние прохода
        printf("  Final: ");
        for (int k = 0; k < n; k++) {
            if (k <= left || k >= right) {
                printf("[%d] ", arr[k]);
            } else {
                printf("%d ", arr[k]);
            }
        }
        printf("\n\n");
        
        pass++;

    } while (swapped);

    printArray(arr, n, "FINAL");
}

// 4. Сортировка Шелла
void shellSort(int arr[], int n) {
    printf("\n========== SORTIROVKA SHELLA ==========\n");
    printArray(arr, n, "Nachalnyj massiv");
    printf("\n");

    int iteration = 1;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        printf("========== Iteratsiya %d: Gap = %d ==========\n", iteration++, gap);
        
        // Показываем на какие подмассивы разделен массив
        printf("Razdelenie na podmassivy:\n");
        for (int start = 0; start < gap; start++) {
            printf("  Podmassiv %d: [", start);
            for (int i = start; i < n; i += gap) {
                printf("%d", arr[i]);
                if (i + gap < n) printf(", ");
            }
            printf("] (indeksy: ");
            for (int i = start; i < n; i += gap) {
                printf("%d", i);
                if (i + gap < n) printf(", ");
            }
            printf(")\n");
        }
        printf("\n");

        // Сортировка с детальным отслеживанием
        printf("Sortirovka podmassivov:\n");
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            int moved = 0;

            while (j >= gap && arr[j - gap] > temp) {
                if (!moved) {
                    printf("  Vstavlyaem %d (pozitsiya %d):\n", temp, i);
                    moved = 1;
                }
                
                printf("    Sdvig: arr[%d]=%d -> arr[%d]\n", j - gap, arr[j - gap], j);
                arr[j] = arr[j - gap];
                j -= gap;
                
                // Промежуточный вывод после каждого сдвига
                printf("           ");
                for (int k = 0; k < n; k++) {
                    printf("%d ", arr[k]);
                }
                printf("\n");
            }
            
            if (moved) {
                arr[j] = temp;
                printf("    Vstavka: %d -> arr[%d]\n", temp, j);
                printf("           ");
                for (int k = 0; k < n; k++) {
                    printf("%d ", arr[k]);
                }
                printf("\n\n");
            }
        }
        
        printArray(arr, n, "Rezultat iteratsii");
        printf("\n");
    }

    printArray(arr, n, "FINAL");
}


void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    int n, choice;

    printf("==============================================\n");
    printf("   PROGRAMMA SORTIROVOK                      \n");
    printf("==============================================\n\n");

    printf("Введите размер массива (от 1 до 100000): ");
    
    if (scanf("%d", &n) != 1) {
        printf("Oshibka vvoda! Vvedite tseloe chislo.\n");
        return 1;
    }

    if (n <= 0) {
        printf("Oshibka: razmer dolzhen byt > 0\n");
        return 1;
    }

    if (n > 100000) {
        printf("Oshibka: razmer slishkom bolshoj (max 100000)\n");
        return 1;
    }

    int* original = (int*)malloc(n * sizeof(int));
    if (original == NULL) {
        printf("Oshibka: ne udalos vydelit pamyat dlya original!\n");
        return 1;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Oshibka: ne udalos vydelit pamyat dlya arr!\n");
        free(original);
        return 1;
    }

    printf("Vvedite %d chisel:\n", n);
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        if (scanf("%d", &original[i]) != 1) {
            printf("Oshibka vvoda! Vvedite tseloe chislo.\n");
            free(original);
            free(arr);
            return 1;
        }
    }

    do {
        printf("\n==============================================\n");
        printf("              MENYU SORTIROVOK               \n");
        printf("==============================================\n");
        printf(" 1. Sortirovka vstavkami\n");
        printf(" 2. Sortirovka vyborom\n");
        printf(" 3. Puzyrykovaya s flagom\n");
        printf(" 4. Sortirovka Shella\n");
        printf(" 5. Shejkernaya sortirovka\n");
        printf(" 0. Vykhod\n");
        printf("==============================================\n");
        printf("Vash vybor: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Oshibka vvoda!\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 0) break;

        if (choice < 0 || choice > 5) {
            printf("Netochno! Vvedite chislo ot 0 do 5.\n");
            continue;
        }

        copyArray(original, arr, n);

        switch (choice) {
            case 1: insertionSort(arr, n); break;
            case 2: selectionSort(arr, n); break;
            case 3: bubbleSort(arr, n); break;
            case 4: shellSort(arr, n); break;
            case 5: shakerSort(arr, n); break;
            default: printf("Netochno! Poprobujte snova.\n");
        }

        printf("\n");
        system("pause");

    } while (choice != 0);

    free(original);
    free(arr);

    printf("\nDo svidaniya!\n");
    return 0;
}