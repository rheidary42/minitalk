# Ubuntu 22.04 (bash 5.1.16)
FROM --platform=linux/amd64 ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && apt-get install -y --no-install-recommends \
	build-essential \
	git \
	gdb \
	libreadline-dev \
	libncurses-dev \
	&& rm -rf /var/lib/apt/lists/*

# Create non-root user
RUN useradd -m -s /bin/bash dev

USER dev
WORKDIR /home/dev/workspace

# Customize shell prompt
RUN echo 'export PS1="\W> "' >> /home/dev/.bashrc

ENTRYPOINT ["/bin/bash", "-lc"]