#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <stddef.h>
#include <stdbool.h>

/** Struktura opisująca bufor kołowy */
typedef struct {
    size_t bufferSize;
    int head;
    int tail;
    int * ptr_buffer;
    int incrementator;
} RingBuffer;

/** Inicjalizacja bufora kołowego 
 * 
 * @param ringBuffer wskaźnik na strukturę bufora
 * @param dataBuffer wskaźnik na pamięć, gdzie dane bufora będą przechowywane
 * @param dataBufferSize rozmiar w bajtach bufora
 * 
 * Program powinien walidować otrzymane dane.
*/
void RingBuffer_Init(RingBuffer * ringBuffer, void * dataBuffer, size_t dataBufferSize);

/** Czszczenie zawartości bufora
 * 
 * @param ringBuffer wskaźnik na strukturę bufora
 * @return true jeśli udało się wyczyścić bufor, w innym przypadku false
 */
bool RingBuffer_Clear(RingBuffer * ringBuffer);

/** Sprawdzenie, czy bufor jest pusty
 * 
 * @param ringBuffer wskaźnik na strukturę bufora
 * @return true jeśli jest pusty, w innym przypadku false
 */
bool RingBuffer_IsEmpty(RingBuffer const * ringBuffer);

/** Sprawdzenie długości bufora
 * 
 * @param ringBuffer wskaźnik na strukturę bufora
 * @return rozmiar w bajtach przechowywanych danych
 */
size_t RingBuffer_GetLength(RingBuffer const * ringBuffer);

/** Sprawdzenie pojemności bufora
 * 
 * @param ringBuffer wskaźnik na strukturę bufora
 * @return rozmiar w bajtach możliwych do przechowania
 */
size_t RingBuffer_getCapacity(RingBuffer const * ringBuffer);

/** Pobierz znak z bufora
 * 
 * Pobiera pojedynczy znak z bufora i dekrementuje jego długość o 1
 * 
 * @param ringBuffer wskaźnik na strukutrę bufora
 * @param c wskaźnik na odebraną daną z bufora
 * @return true jeśli znak został poprawnie pobrany, w innym przypadku false
 */
bool RingBuffer_GetChar(RingBuffer * ringBuffer, char * c);

/** Załaduj znak do bufora 
 * 
 * Dodaje pojedynczy znak do bufora i inkrementuje jego długość o 1
 * @param ringBuffer wskaźnik na strukutrę bufora
 * @param c wstawiany znak
 * @return true jeśli znak dodał poprawnie wstawiony, w innym przypadku false
*/
bool RingBuffer_PutChar(RingBuffer * ringBuffer, char c);

#endif