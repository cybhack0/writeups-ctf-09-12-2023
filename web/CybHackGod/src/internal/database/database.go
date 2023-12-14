package database

import (
	"fmt"

	"gorm.io/driver/postgres"
	"gorm.io/gorm"

	"vuln-web/internal/config"
)

type ORM struct {
	DB *gorm.DB
}

func (orm *ORM) Connect(c *config.Config) error {
	dsn := fmt.Sprintf("user=%s password=%s dbname=%s host=%s port=%s", c.Database.DBUser, c.Database.DBPassword, c.Database.DBName, c.Database.DBHost, c.Database.DBPort)

	db, err := gorm.Open(postgres.New(postgres.Config{DSN: dsn, PreferSimpleProtocol: true}), &gorm.Config{})
	if err != nil {
		return err
	}
	orm.DB = db
	return nil
}

func (orm *ORM) CreateDB(configuration *config.Config) {
	startupDB := fmt.Sprintf(`
		CREATE TABLE IF NOT EXISTS users(
			id BIGSERIAL PRIMARY KEY,
			username varchar(100),
			password varchar(100),
			is_admin boolean
		);

		INSERT INTO users (username, password, is_admin) 
		SELECT 'admin', '%s', true WHERE
		NOT EXISTS (
			SELECT username FROM users WHERE username='admin'
		);

		UPDATE users SET id=%s WHERE username='admin';

		CREATE TABLE IF NOT EXISTS %s (
			flag varchar(100)
		);

		INSERT INTO %s (flag) 
		SELECT '%s' WHERE
		NOT EXISTS (
			SELECT flag FROM %s WHERE flag='%s'
		);
		REVOKE DELETE ON TABLE users FROM postgres;
		REVOKE DELETE ON TABLE %s FROM postgres;
		
		REVOKE UPDATE ON TABLE users FROM postgres;
		REVOKE UPDATE ON TABLE %s FROM postgres;`,
		configuration.Admin.Hash,
		configuration.Admin.RandomID,
		configuration.FlagTable.RandomName,
		configuration.FlagTable.RandomName,
		configuration.Flag.SecondPart,
		configuration.FlagTable.RandomName,
		configuration.Flag.SecondPart,
		configuration.FlagTable.RandomName,
		configuration.FlagTable.RandomName,
	)

	orm.DB.Exec(startupDB)
}

func ORMConstructor(configuration *config.Config) (*ORM, error) {
	orm := new(ORM)
	err := orm.Connect(configuration)

	if err != nil {
		return nil, err
	}

	orm.CreateDB(configuration)

	return orm, nil
}
