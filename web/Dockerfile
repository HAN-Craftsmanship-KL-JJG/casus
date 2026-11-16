# Builds the React frontend and puts it in a Caddy image.
FROM node:24.22.3-alpine AS build

WORKDIR /src

# Own layer: the packages only reinstall when the lock file changes.
COPY package.json package-lock.json ./
RUN npm ci

COPY index.html tsconfig.json vite.config.ts ./
COPY src ./src
RUN npm run build

FROM caddy:2.11.9-alpine

COPY Caddyfile /etc/caddy/Caddyfile
COPY --from=build /src/dist /srv
