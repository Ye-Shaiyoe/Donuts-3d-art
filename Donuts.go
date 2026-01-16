package main

import (
	"fmt"
	"math"
	"time"
)

func main() {
	A, B := 0.0, 0.0
	
	shade := ".,-~:;=!*#$@"
	colors := []string{
		"\x1b[34m",
		"\x1b[36m", 
		"\x1b[32m", 
		"\x1b[92m", 
		"\x1b[93m", 
		"\x1b[91m",
		"\x1b[95m", 
		"\x1b[97m",
	}
	

	fmt.Print("\x1b[2J")
	
	for {

		z := make([]float64, 1760)
		b := make([]byte, 1760)
		color := make([]int, 1760)
		
		for k := 0; k < 1760; k++ {
			b[k] = ' '
		}
		
		for j := 0.0; j < 6.28; j += 0.07 {
			for i := 0.0; i < 6.28; i += 0.02 {
				c := math.Sin(i)
				d := math.Cos(j)
				e := math.Sin(A)
				f := math.Sin(j)
				g := math.Cos(A)
				h := d + 2
				D := 1 / (c*h*e + f*g + 5)
				l := math.Cos(i)
				m := math.Cos(B)
				n := math.Sin(B)
				t := c*h*g - f*e
				
				x := int(40 + 30*D*(l*h*m - t*n))
				y := int(12 + 15*D*(l*h*n + t*m))
				o := x + 80*y
				N := int(8 * ((f*e - c*d*g)*m - c*d*e - f*g - l*d*n))
				
				if y > 0 && y < 22 && x > 0 && x < 80 && o >= 0 && o < 1760 {
					if D > z[o] {
						z[o] = D
						if N < 0 {
							N = 0
						}
						if N > 11 {
							N = 11
						}
						b[o] = shade[N]
						color[o] = N % 8
					}
				}
			}
		}
		

		fmt.Print("\x1b[H")
		

		for k := 0; k < 1760; k++ {
			if k%80 != 0 {
				fmt.Print(colors[color[k]], string(b[k]))
			} else {
				fmt.Println()
			}
		}

		fmt.Print("\x1b[0m")
		
		A += 0.04
		B += 0.02


// how to run this -> go run Donuts.go

		time.Sleep(30 * time.Millisecond)
	}
}
