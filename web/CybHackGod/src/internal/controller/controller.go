package controller

import (
	"net/http"

	"github.com/labstack/echo/v4"

	"vuln-web/internal/config"
	"vuln-web/internal/database"
	"vuln-web/internal/database/models"
	"vuln-web/internal/template"
	"vuln-web/utils/hash"
	"vuln-web/utils/jwt"
)

type Server struct {
	config *config.Config
	orm    *database.ORM
}

func (s *Server) SetConfig() error {
	conf, err := config.ConfigConstructor()
	if err != nil {
		return err
	}
	s.config = conf
	return nil
}

func (s *Server) SetORM() error {
	var err error
	s.orm, err = database.ORMConstructor(s.config)
	if err != nil {
		return err
	}
	return nil
}

func (s *Server) Run() {
	e := echo.New()
	e.Static("/static", "runtime/static")

	t := template.TemplateGenerator()

	e.Renderer = t

	e.GET("/", s.index)
	e.GET("/index", s.index)
	e.GET("/ping", s.ping)
	e.GET("/login", s.login)
	e.GET("/register", s.register)
	e.GET("/profile", s.profile)
	e.GET("/admin", s.admin)
	e.GET("/logout", s.logout)

	e.POST("/login", s.loginPOST)
	e.POST("/register", s.registerPOST)

	e.Logger.Fatal(e.Start(s.config.Server.Host))
}

func (s *Server) index(c echo.Context) error {
	return c.Render(http.StatusOK, "index.html", map[string]interface{}{})
}

func (s *Server) logout(c echo.Context) error {
	cookie := new(http.Cookie)
	cookie.Name = "AuthToken"
	cookie.Value = ""

	c.SetCookie(cookie)

	return c.Redirect(http.StatusFound, "/")
}

func (s *Server) ping(c echo.Context) error {
	return c.String(http.StatusOK, "pong!")
}

func (s *Server) register(c echo.Context) error {
	cookie, err := c.Cookie("AuthToken")

	if err != nil {
		return c.Render(http.StatusOK, "register.html", map[string]interface{}{})
	}

	json, jwterr := jwt.DecodeJWT(cookie.Value)
	if jwterr != nil {
		cookie := new(http.Cookie)
		cookie.Name = "AuthToken"
		cookie.Value = ""

		c.SetCookie(cookie)
		return c.Render(http.StatusOK, "register.html", map[string]interface{}{})
	}

	// Deleted accounts
	users := new(models.User)
	resault := s.orm.DB.Find(users, "id=?", json["id"])
	if resault.RowsAffected == 0 {
		cookie := new(http.Cookie)
		cookie.Name = "AuthToken"
		cookie.Value = ""

		c.SetCookie(cookie)
		return c.Render(http.StatusOK, "register.html", map[string]interface{}{})
	}

	return c.Redirect(http.StatusFound, "/profile")
}

func (s *Server) registerPOST(c echo.Context) error {
	username := c.FormValue("username")
	password := c.FormValue("password")

	if len(username) == 0 || len(password) == 0 {
		return c.Redirect(http.StatusFound, "/register")
	}

	users := new(models.User)
	resault := s.orm.DB.Find(users, "username=?", username)

	if resault.RowsAffected != 0 {
		return c.Redirect(http.StatusFound, "/register")
	}

	user := models.User{Username: username, Password: hash.MD5Sum(password), IsAdmin: false}
	s.orm.DB.Create(&user)

	return c.Redirect(http.StatusFound, "/login")
}

func (s *Server) login(c echo.Context) error {
	cookie, err := c.Cookie("AuthToken")

	if err != nil {
		return c.Render(http.StatusOK, "login.html", map[string]interface{}{})
	}

	json, jwterr := jwt.DecodeJWT(cookie.Value)
	if jwterr != nil {
		cookie := new(http.Cookie)
		cookie.Name = "AuthToken"
		cookie.Value = ""

		c.SetCookie(cookie)
		return c.Render(http.StatusOK, "login.html", map[string]interface{}{})
	}

	users := new(models.User)
	resault := s.orm.DB.Find(users, "id=?", json["id"])
	if resault.RowsAffected == 0 {
		cookie := new(http.Cookie)
		cookie.Name = "AuthToken"
		cookie.Value = ""

		c.SetCookie(cookie)
		return c.Render(http.StatusOK, "login.html", map[string]interface{}{})
	}

	return c.Redirect(http.StatusFound, "/profile")
}

func (s *Server) loginPOST(c echo.Context) error {
	username := c.FormValue("username")
	password := c.FormValue("password")

	if len(username) == 0 || len(password) == 0 {
		return c.Redirect(http.StatusFound, "/login")
	}

	users := new(models.User)
	resault := s.orm.DB.Find(users, "username=? AND password=?", username, hash.MD5Sum(password))

	if resault.RowsAffected == 0 {
		return c.Redirect(http.StatusFound, "/login")
	}

	user := new(models.User)
	s.orm.DB.Find(user, "username=? AND password=?", username, hash.MD5Sum(password))

	token := jwt.EncodeJWT(user.ID)

	cookie := new(http.Cookie)
	cookie.Name = "AuthToken"
	cookie.Value = token

	c.SetCookie(cookie)
	return c.Redirect(http.StatusFound, "/profile")
}

func (s *Server) profile(c echo.Context) error {
	cookie, err := c.Cookie("AuthToken")

	if err != nil {
		return c.Redirect(http.StatusFound, "/login")
	}

	json, jwterr := jwt.DecodeJWT(cookie.Value)
	if jwterr != nil {
		cookie := new(http.Cookie)
		cookie.Name = "AuthToken"
		cookie.Value = ""

		c.SetCookie(cookie)
		return c.Redirect(http.StatusFound, "/login")
	}

	users := new(models.User)
	resault := s.orm.DB.Find(users, "id=?", json["id"])
	if resault.RowsAffected == 0 {
		cookie := new(http.Cookie)
		cookie.Name = "AuthToken"
		cookie.Value = ""

		c.SetCookie(cookie)
		return c.Redirect(http.StatusFound, "/login")
	}

	user := new(models.User)
	s.orm.DB.First(user, "id=?", json["id"])
	return c.Render(http.StatusOK, "profile.html", map[string]interface{}{
		"name": user.Username,
	})
}

func (s *Server) admin(c echo.Context) error {
	cookie, err := c.Cookie("AuthToken")

	if err != nil {
		return c.Redirect(http.StatusFound, "/login")
	}

	json, jwterr := jwt.DecodeJWT(cookie.Value)

	if jwterr != nil {
		cookie := new(http.Cookie)
		cookie.Name = "AuthToken"
		cookie.Value = ""

		c.SetCookie(cookie)
		return c.Redirect(http.StatusFound, "/login")
	}

	user := new(models.User)
	s.orm.DB.First(user, json["id"])

	if !user.IsAdmin {
		return c.Redirect(http.StatusFound, "/profile")
	}

	return c.Render(http.StatusOK, "admin.html", map[string]interface{}{
		"flag_part_one": s.config.Flag.FirstPart,
	})
}

func ServerConstructor() (*Server, error) {
	server := new(Server)
	err := server.SetConfig()
	if err != nil {
		return nil, err
	}
	server.SetORM()

	if !jwt.IsSultExists() {
		jwt.CreateSult()
	}
	return server, nil
}
