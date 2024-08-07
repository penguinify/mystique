/** @type {import('tailwindcss').Config} */
module.exports = {
    content: ["./*.html", "./js/*.js"],
  theme: {
    extend: {
        fontFamily: {
            'sans': ['Nunito', 'sans-serif'],
            'mono': ['Inconsolata', 'monospace'],
        },
        }
    },
plugins: [require("@catppuccin/tailwindcss")({
    defaultFlavour: "frappe",
})],
}

