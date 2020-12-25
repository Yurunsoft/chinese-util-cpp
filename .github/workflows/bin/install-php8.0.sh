#!/bin/bash

add-apt-repository ppa:ondrej/php -y -u

apt-get update

apt install -y gcc php8.0-cli php8.0-bcmath php8.0-curl php8.0-dev hp8.0-mbstring php8.0-zip

php -v
php -m
php-config

curl -o composer.phar https://getcomposer.org/composer-stable.phar && chmod +x composer.phar && sudo mv -f composer.phar /usr/local/bin/composer && composer -V;

phpdismod xdebug
