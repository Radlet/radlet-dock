<p align="center">
  <a href="" rel="noopener">
 <img src="./docs/twitter_header_photo_2.png" alt="Project logo"></a>
</p>

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
![Docker Image CI](https://github.com/Radlet/radlet-dock/workflows/Docker%20Image%20CI/badge.svg?branch=add_submodule_cpr)
[![GitHub Issues](https://img.shields.io/github/issues/Radlet/radlet-dock)](https://github.com/Radlet/radlet-dock/issues)
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/Radlet/radlet-dock)](https://github.com/Radlet/radlet-dock/pulls)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>
<br/> 

<h1 align="center">Radlet Dock</h1>

---

The Radlet ecosystem was created keeping *speed* and *flexibility* in mind and thus making edge computing a little more easier for people who wish to tinker. The existing IOT solutions are either proprietary or are too tightly coupled for a regular user to tinker with. We bring the speed of coupled system and the flexibility of a decoupled system with the perfectly balanced IOT ecosystem - Radlet. The ecosystem consists of **three primary components** out of which this repository hold the code for **Radlet-Dock**.
    <br> 


## Table of Contents :octocat:

- [Structure](#structure)
- [Getting Started](#getting_started)
- [Deployment](#deployment)
- [Usage](#usage)
- [Built Using](#built_using)
- [Authors](#authors)

## 1. Structure :snowflake: <a name = "structure"></a>

The internal structure of our dock is according to the block diagram that follows. This is done so that users can tinker with the system easily and swap in and our things according to their needs.
<img width=800px height=550px src="./docs/prototype.png" alt="Project Plan"></a>

## 2. Getting Started :four_leaf_clover: <a name = "getting_started"></a>

To make things easier for everyone we have made use of docker for build testing and deployment. This takes away most of the problems that you might face during project setup which includes library installation, environment variable setup etc. For the upcoming steps to work, you need the following applications installed on your OS.

### 2.a Prerequisites

- Docker
- Docker-Compose
- Git

### 2.b Build

The build step makes use of docker that comes packed with all the necessary libraries that we are using. Under the hood, it pulls the **humbled/radlet_dock.env** image from docker hub and attempts to create a new **radlet_dock.dev**  image. The following command is used not only for image creation but also for build testing. If the image creation exits with a non-zero code, then the build was not successful.  
  
Run the following command from project root:
```bash
./package.sh -b
```
  
### 2.c Manual test / Run

After a **radlet_dock.dev** image has been created we can manually test the dock by running it. For it, we will open an interactive shell in the docker container and run the dock binary.  
  
Run the following command from project root:
```bash
./package.sh -mt
./bin/radlet_dock
```  
  
---  

## 3. Deployment :fire: <a name = "deployment"></a>

For the purpose of deployment, we can straight away use the docker hub image. The deployment is kept upto date by our team.  
[![Docker](https://img.shields.io/docker/pulls/radlet/radlet_dock?style=for-the-badge)](https://hub.docker.com/repository/docker/radlet/radlet_dock)  
  
To run the deployment build, simply run the following command:
```bash
./package.sh -d
```  
---

## 4. Usage :closed_book: <a name="usage"></a>

Once the deployment build has been started in a container the dock is ready to accept IOT devices and user requests for device orchestration. You can use our phone app [Radlet-Composer](https://github.com/Radlet/radlet-composer) and ESP8266 compatible firmware [Radlet-Plankton](https://github.com/Radlet/radlet-plankton) to test out an IOT device in the Radlet ecosystem.

---

## 5. Built Using :nail_care: <a name = "built_using"></a>

Check project wiki to know more...

---

## 6. Authors :hammer: <a name = "authors"></a>

- [@AakashMallik](https://github.com/AakashMallik)  
- [@dhirajfx3](https://github.com/dhirajfx3)
