set number
set relativenumber
set autoindent
set tabstop=4
set shiftwidth=4
set smarttab
set softtabstop=4
set mouse=a
set cursorline 
set signcolumn=yes
" Below 3 in from TreeSitter github(official)
set foldmethod=expr
set foldexpr=nvim_treesitter#foldexpr()
set nofoldenable " Disable folding at startup.

set foldmethod=syntax 
set foldcolumn=1
" :set splitbelow splitright
" CHATGTP 3.5 SUGGESTED
set smartindent  " auto-indentation based on the syntax 
set hlsearch     " Highlights search matches as you type
set expandtab    " uses spaces instead of tabs

" Below line was said a must to enaable vim-commentary
filetype plugin indent on "to comment out a line •gcc to CO. selection •gc
"End : to install vim-commentary visit https://github.com/tpope/vim-commentary


call plug#begin()

Plug 'http://github.com/tpope/vim-surround' " Surrounding ysw)
Plug 'https://github.com/preservim/nerdtree' " NerdTree
Plug 'https://github.com/tpope/vim-commentary' " For Commenting gcc & gc
Plug 'https://github.com/vim-airline/vim-airline' " Status bar
Plug 'https://github.com/lifepillar/pgsql.vim' " PSQL Pluging needs :SQLSetType pgsql.vim
Plug 'https://github.com/ap/vim-css-color' " CSS Color Preview
Plug 'https://github.com/rafi/awesome-vim-colorschemes' " Retro Scheme
Plug 'https://github.com/neoclide/coc.nvim'  " Auto Completion
Plug 'https://github.com/ryanoasis/vim-devicons' " Developer Icons
Plug 'https://github.com/tc50cal/vim-terminal' " Vim Terminal
Plug 'https://github.com/preservim/tagbar' " Tagbar for code navigation
Plug 'https://github.com/terryma/vim-multiple-cursors' " CTRL + N for multiple cursors

" CHATGPT SUGGESTED PLUGIN
" Plug 'jiangmiao/auto-pairs'
Plug 'neoclide/coc.nvim', {'branch': 'release'}
Plug 'mhinz/vim-signify' "vertical line beside code vlock
" fuzzy finder from github
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'
" vertical line alone braces
Plug 'Yggdroot/indentLine'
" Treesitter Github/Youtube recommended// must: visit github repo
Plug 'nvim-treesitter/nvim-treesitter', {'do': ':TSUpdate'}
Plug 'kassio/neoterm' "CHATGTP :term customize, to open below

set encoding=UTF-8

call plug#end()

:colorscheme jellybeans 



nnoremap <C-f> :NERDTreeFocus<CR>
nnoremap <C-n> :NERDTree<CR>
nnoremap <C-t> :NERDTreeToggle<CR>
nnoremap <C-l> :call CocActionAsync('jumpDefinition')<CR>
nnoremap <silent> <C-s> :w<CR>
nmap <F8> :TagbarToggle<CR>

:set completeopt-=preview " For No Previews


let g:NERDTreeDirArrowExpandable="+"
let g:NERDTreeDirArrowCollapsible="~"

" --- Just Some Notes ---
" :PlugClean :PlugInstall :UpdateRemotePlugins
"
" :CocInstall coc-python
" :CocInstall coc-clangd
" :CocInstall coc-snippets
" :CocCommand snippets.edit... FOR EACH FILE TYPE

" air-line
let g:airline_powerline_fonts = 1

if !exists('g:airline_symbols')
    let g:airline_symbols = {}
endif

" airline symbols
let g:airline_left_sep = ''
let g:airline_left_alt_sep = ''
let g:airline_right_sep = ''
let g:airline_right_alt_sep = ''
let g:airline_symbols.branch = ''
let g:airline_symbols.readonly = ''
let g:airline_symbols.linenr = ''
let g:neoterm_default_mod = 'belowright'

inoremap <expr> <Tab> pumvisible() ? coc#_select_confirm() : "<Tab>"

"CHATGPT SUGGESTED
"let g:AutoPairsFlyMode = 1
"autocmd FileType c,cpp lua require('nvim-autopairs').filetype_ignore['c'] = {'help'}

"# CHATGPT SUGGESTED FOR GETTING C++ SUGGESTIONS IN CODING
" Use tab for trigger completion and navigate to the next complete item
inoremap <silent><expr> <TAB> pumvisible() ? "\<C-n>" : "\<TAB>"
inoremap <expr><S-TAB> pumvisible() ? "\<C-p>" : "\<C-h>"

" Use <C-space> to trigger completion.
inoremap <silent><expr> <C-space> coc#refresh()

" Set the maximum width of the completion menu
let g:coc_global_extensions = [
    \ 'coc-snippets',
    \ 'coc-pairs',
    \ 'coc-highlight',
    \ 'coc-json',
    \ 'coc-lists',
    \ 'coc-yank',
    \ 'coc-prettier',
    \ 'coc-explorer',
    \ ]

" Use coc for C++ (you may need to install ccls)
autocmd FileType cpp,c,objc inoremap <silent><buffer> <C-Space> <cmd>call <SID>show_documentation()<CR>

function! s:show_documentation()
    if (index(['vim','help'], &filetype) >= 0)
        execute 'h '.expand('<cword>')
    else
        call CocActionAsync('doHover')
    endif
endfunction
" SUGGESTION END FROM CHATGPT


" CHATGPT SEESTION FOR INSTALLING CCLS
let g:coc_global_extensions = [
    \ 'coc-snippets',
    \ 'coc-pairs',
    \ 'coc-highlight',
    \ 'coc-json',
    \ 'coc-lists',
    \ 'coc-yank',
    \ 'coc-prettier',
    \ 'coc-explorer',
    \ 'coc-ccls',
    \ ]
" CHATGOT SUGGESTION END FOR INSTALL CCLS





" CHATGTP CONFIG FOR SIGNIFY PLIGIN START
" Enable Signify for Git integration
nmap <silent> <\>gs :SignifyToggle<CR>
" Enable code folding column
let g:signify_sign_fold_enable = 1
" GHATGPT ENDS
"
" Adding C compiler for nvim-reesitter
let g:reesitter#install#compilers = ['clang']

" Set ripgrep as the default file search tool
let g:telescope_find_command = ['rg', '--hidden', '--files']
