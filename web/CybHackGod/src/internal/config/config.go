package config

import (
	"os"
)

type Config struct {
	Server struct {
		Host string
	}
	Database struct {
		DBHost     string
		DBName     string
		DBUser     string
		DBPassword string
		DBPort     string
	}
	Admin struct {
		Hash     string
		RandomID string
	}
	FlagTable struct {
		RandomName string
	}
	Flag struct {
		FirstPart  string
		SecondPart string
	}
}

func ConfigConstructor() (*Config, error) {

	conf := new(Config)

	conf.Database.DBName = os.Getenv("POSTGRES_DB")
	conf.Database.DBUser = os.Getenv("POSTGRES_USER")
	conf.Database.DBPassword = os.Getenv("POSTGRES_PASSWORD")
	conf.Database.DBHost = os.Getenv("POSTGRES_HOST")
	conf.Database.DBPort = os.Getenv("POSTGRES_PORT")

	conf.Server.Host = os.Getenv("SERVER_HOST")

	conf.Admin.Hash = os.Getenv("ADMIN_PASSWORD_HASH")
	conf.Admin.RandomID = os.Getenv("RANDOM_ADMIN_ID")

	conf.FlagTable.RandomName = os.Getenv("RANDOM_TABLE_SYMBOLS")

	conf.Flag.FirstPart = os.Getenv("FLAG_FIRST_PART")
	conf.Flag.SecondPart = os.Getenv("FLAG_SECOND_PART")

	return conf, nil
}
