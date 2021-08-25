# Processo Seletivo 42 São Paulo: 42Labs

This project was made for École 42 São Paulo Labs. Its aim was to create an API
in C for parsing data from the Intranet users.

Core concepts learned in this project:

1. How HTTP requests/responses work.
2. What exactly is an API and its inner workings.
3. How to make API integration tests.
4. How to create Docker/Vagrant containers and when/how to use them.
5. Continuous Integration philosophy.

![Build](https://github.com/42sp/42labs-selection-process-vinicius507/actions/workflows/build.yml/badge.svg)
![Norminette](https://github.com/42sp/42labs-selection-process-vinicius507/actions/workflows/norminette.yml/badge.svg)

API Reference
---

> To run the application you need to register an Intranet v2 Application at [intra](https://intra.42.fr/)

### Overview

The 42Stats API v1 is responsable for giving stats on École 42 Students.

### HTTP Reference

- URL: `/v1/{INTRA_LOGIN}`

- Method: `GET`

- Success Response:
	- Code: `200`
	- Content:
	```json
		{
			"intra_id": 86692,
			"login": "vgoncalv",
			"name": "Vinícius Gonçalves De Oliveira",
			"staff": false,
			"finished_projects": 24,
			"gpa": 99.21,
			"stardew_coefficient": 0.61
		}
	```

### Extending the API

The API is coded in a way to easily add and/or modify endpoints.

The following `enum` serves for referencing registered routes:

```c
enum e_routes
{
	API_V1_,
	API_V1_USER,
	ROUTES,
};

```

By adding another `enum` value before the value `ROUTES`, you can
register a new endpoint for the API using:

```c
	register_route(GET, API_V1_, redirect, &api);
	register_route(GET, API_V1_USER, get_user_data, &api);
```

Where `redirect` and `get_user_data` are the callbacks for the
endpoint.

Usage
---

You need to place your Intranet v2 Application `CLIENT-ID` and `SECRET`,
alongside with MongoDB `DB_ADDRESS` in  a `.env` file.

```env
DB_ADDRESS=YOUR_MONGODB_CONNECTION_STRING
CLIENT_ID=YOUR_INTRANET_APPLICATION_UID
CLIENT_SECRET=YOUR_INTRANET_APPLICATION_SECRET
```

### Docker

```bash
docker build -t vgoncalv/ft_stats:0.2
docker run -t -p 4242:4242 --env-file .env vgoncalv/ft_stats:0.2
```

### Vagrant

To run it with Vagrant you need the plugin `vagrant-vbguest`.

```bash
vagrant up
```

### Manual Installation as Systemd service

First you need to install the dependencies:

```bash
sudo apt update
sudo apt install libmbedtls-dev \
		clang \
		make \
		libmongoc-1.0-0 \
		libmongoc-dev
```

Then run:

```bash
sudo make install
```
