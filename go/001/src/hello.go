package main

import (
	"001/pkg/jgkim/goSwitch"
	"fmt"
)

func main() {
	// Raw String Literal. 복수라인.
	rawLiteral := `아리랑\n
아리랑\n
  아라리요`

	// Interpreted String Literal
	interLiteral := "아리랑아리랑\n아리리요"
	// 아래와 같이 +를 사용하여 두 라인에 걸쳐 사용할 수도 있다.
	// interLiteral := "아리랑아리랑\n" +
	//                 "아리리요"

	fmt.Println(rawLiteral)
	fmt.Println()
	fmt.Println(interLiteral)

	k := 10
	var p = &k      // k의 주소를 할당
	fmt.Println(*p) // p가 가리키는 주소에 있는 실제 내용을 출력
	fmt.Println(p)  // p가 가리키는 주소를 출력

	if k == 1 {
		println("One")
	} else if k == 2 { //같은 라인
		println("Two")
	} else { //같은 라인
		println("Other")
	}

	switch1()
	goSwitch.Grade(10)
	var music = goSwitch.GetMusic("Adele")
	fmt.Println(music)

	var sum = goSwitch.Sum(100)
	fmt.Println(sum)
}

func switch1() {
	var name string
	var category = 1

	switch category {
	case 1:
		name = "Paper Book"
	case 2:
		name = "eBook"
	case 3, 4:
		name = "Blog"
	default:
		name = "Other"
	}
	println(name)
}
