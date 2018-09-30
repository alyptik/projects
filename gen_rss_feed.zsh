#!/usr/bin/env zsh

die() { printf "ERROR: %s\n" "$@" 1>&2; exit 1 }

readonly zegaledir="${XDG_DATA_DIR:-$HOME/.local/share}"/zegale
mkdir -p "$zegaledir"

if [[ "$1" = "-" ]]; then
	readonly file="/dev/stdin"
else
	readonly file="$zegaledir"/feedlist
fi

fetch_feed() {
	local url="$1"
	[[ -z "$url" ]] && die "Got empty URL argument"

	local title="$2"
	[[ -z "$title" ]] && die "Got empty title argument"

	local domain="$(sed -rn 's,.+://([^/]+).*,\1,p' <<<"$url")"
	local feeddb="$zegaledir"/db/"$domain"/"$title"
	mkdir -p "$feeddb"

	local stagefile="$(mktemp -t zegale-stage."$domain"."$title".XXXXXX)"
	trap "rm '$stagefile'" EXIT

	if curl -sL "$url" -o "$stagefile"; then
		xsltproc "$zegaledir"/feed.xslt "$stagefile" > "$feeddb"/incoming
	fi
}

extract_new() {
	local db
	for db in "$zegaledir"/db/*/*; do
		if [[ ! -f "$db"/incoming ]]; then
			continue
		fi

		if [[ -f "$db"/all ]]; then
			grep -Fxvf "$db"/all -- "$db"/incoming > "$db"/new
			rm "$db"/incoming
		else
			mv "$db"/incoming "$db"/new
		fi
	done
}

process_new() {
	local db
	for db in "$zegaledir"/db/*/*; do
		if [[ ! -f "$db"/new ]]; then
			continue
		fi

		local new="$(wc -l < "$db"/new)"
		if [[ "$new" -gt 0 ]]; then
			printf '\a\e[1m[%s] %s\e[0m\n' "$new" "${db##*/}"
			while read -r url title; do
#				printf '\e]8;;%s\a%s\e]8;;\a \e[0;34m<%s>\e[0m\n' "$url" "$title" "$url"
				printf '%s \e[0;34m<%s>\e[0m\n' "$title" "$url"
			done < "$db"/new
		fi
		cat -- "$db"/new "$db"/all 2>/dev/null | sponge "$db"/all
		rm -- "$db"/new
	done
}

nl -w 1 -b a "$file" | while read -r number url title; do
	if [[ -z "$url" || -z "$title" ]]; then
		die "Invalid feed specification on line $number"
	fi
	fetch_feed "$url" "$title" &
done

wait
extract_new
process_new
