package jwt

import (
	"encoding/json"
	"errors"
	"fmt"
	"log"
	"math"
	"os"
	"strconv"
	"time"

	jwt "github.com/dgrijalva/jwt-go"
)

type JWTRandomSeed struct {
	Seed_time int
}

func IsSultExists() bool {
	if _, err := os.Stat("etc/sult.json"); errors.Is(err, os.ErrNotExist) {
		return false
	}
	return true
}

func CreateSult() {
	rawSaultJSON := []byte(fmt.Sprintf("{\"seed_time\":%.f}", math.Pow(float64(time.Now().Unix()), float64(time.Now().Day()%2+3))))
	os.WriteFile("etc/sult.json", rawSaultJSON, 0644)
}

func GetJWTSecret() []byte {
	raw_json_sult, err := os.ReadFile("etc/sult.json")
	if err != nil {
		log.Fatal("No file")
	}

	var jwt_sult JWTRandomSeed

	json.Unmarshal(raw_json_sult, &jwt_sult)

	return []byte(strconv.Itoa(jwt_sult.Seed_time))

}

func DecodeJWT(JWT string) (jwt.MapClaims, error) {
	secretKey := GetJWTSecret()
	token, err := jwt.Parse(JWT, func(token *jwt.Token) (interface{}, error) {
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", token.Header["alg"])
		}
		return secretKey, nil
	})

	if err != nil {
		return nil, err
	}

	claims, _ := token.Claims.(jwt.MapClaims)
	return claims, nil
}

func EncodeJWT(id int) string {
	token := jwt.New(jwt.SigningMethodHS256)
	claims := token.Claims.(jwt.MapClaims)
	claims["id"] = id

	secretKey := GetJWTSecret()

	signedToken, err := token.SignedString(secretKey)
	if err != nil {
		panic(err)
	}
	return signedToken
}
