%%writefile priorityqueue.go
package main

/*Implementes a priority queue using channel passing with a buffer */

type PriorityMessage struct {
    Priority int // between 0 and 9
    Message string
}

func priorityQueue(west chan PriorityMessage, east chan string) {

    const C = 20                   //Max amount of elements in buffer
    var buffer [C] PriorityMessage //Create buffer of PriorityMessage
    var in, out, n int

    for {
        if n == C {   /*If your buffer is full remove an element, however, it is assumed that printToScreen 
                        has been called at some point before the first C items are arriving from channel west.*/
            east <- buffer[out % C].Message; out, n = out + 1, n - 1

        } else if n == 0 { //If your buffer is empty, store first element from west
            select {
                case buffer[in % C] = <- west: in, n = in + 1, n + 1
                default:  //If your buffer is empty and you have no inputs, just do nothing
            }

        } else {     //Otherwise store into buffer or print value if printToScreen is called
            select {
                case east <- buffer[out % C].Message: out, n = out + 1, n - 1
                case buffer[in % C] = <- west: 
                
                    /*Insert the element in the buffer by inserting it at the end of the
                    buffer and swapping it with the element to the left until it reaches
                    the front of the buffer or it is not less than the element to the left 
                    of it (this is just essentially insertion sort). */
                    k := in
                    for k > out && (buffer[(k-1) % C].Priority > buffer[k % C].Priority){
                        buffer[(k-1) % C], buffer[k % C] = buffer[k % C], buffer[(k-1) % C]                      
                        k = k - 1
                    }
                    in, n = in + 1, n + 1
            }
        }
    }
}

var west chan PriorityMessage
var east chan string

func printToScreen() {
    for {println(<- east)}
}
func main() {
    west = make(chan PriorityMessage)
    east = make(chan string)
    go priorityQueue(west, east)
    west <- PriorityMessage{1, "one"}
    west <- PriorityMessage{0, "zero"}
    west <- PriorityMessage{2, "two"}
    west <- PriorityMessage{1, "another one"}
    west <- PriorityMessage{0, "another zero"}
    go printToScreen()
    select {} // to allow all messages to be printed
}