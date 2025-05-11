#!/bin/bash

<<comment
#[[ "$(git rev-parse --is-inside-work-tree 2>/dev/null || echo false)" == true && "$(pwd)" != "$(git rev-parse --show-toplevel 2>/dev/null)" ]] && { return 1; }

tool_path_checker() {
    if [[ "$(git rev-parse --is-inside-work-tree 2>/dev/null || echo false)" == true && "$(pwd)" != "$(git rev-parse --show-toplevel 2>/dev/null)" ]]; then
        return 1
    fi
}
comment