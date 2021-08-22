# Processo Seletivo 42 São Paulo: 42Labs

![Build](https://github.com/42sp/42labs-selection-process-vinicius507/actions/workflows/build.yml/badge.svg)
![Norminette](https://github.com/42sp/42labs-selection-process-vinicius507/actions/workflows/norminette.yml/badge.svg)

API Reference
---

### Overview

The 42Stats API v1 is responsable for giving stats on École 42 Students.

### HTPP Reference

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

### Docker

```bash
docker build -t vgoncalv/ft_stats:0.2
docker run -t -p 4242:4242 vgoncalv/ft_stats:0.2
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
