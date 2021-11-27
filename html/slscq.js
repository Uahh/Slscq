let data;
fetch('../data.json').then(data=>data.json()).then(_data=>{
    data = _data;
});

let random_num_cache=[]
const get_random_num = total =>{
    let tmp = Math.floor(Math.random()*total);
    while(random_num_cache.includes(tmp)){
        tmp = Math.floor(Math.random()*total);
    }
    random_num_cache.push(tmp)
    random_num_cache.length>3?random_num_cache.shift():0
    return tmp
}
const get_random = arr=>arr[get_random_num(arr.length)];
const get_title = _=>get_random(data['title']);
const get_noun = _=>get_random(data['noun']);
const get_verb = _=>get_random(data['verb']);
const get_adverb = type=>{
    switch(type){
        case 1:
            return get_random(data['adverb_1']);
        case 2:
            return get_random(data['adverb_2']);
    }
    return '';
};
const get_phrase = _=>get_random(data['phrase']);
const get_sentence = _=>get_random(data['sentence']);
const get_parallel_sentence = _=>get_random(data['parallel_sentence']);
const get_beginning = _=>get_random(data['beginning']);
const get_body = _=>get_random(data['body']);
const get_ending = _=>get_random(data['ending']);
const replace_key = (str,key,theme)=>str.replace(new RegExp(key,'g'),theme);
const replace_xx = (str,theme)=>replace_key(str,'xx',theme)
const replace_vn = str=>replace_key(str,/vn/g,_=>{
    const vns = [];
    vns.length = get_random_num(4) + 1;
    vns.fill(0);
    return vns.map(_=>get_verb()+get_noun()).join('，');
});
const replace_v = str=>replace_key(str,'v',get_verb)
const replace_n = str=>replace_key(str,'n',get_noun)
const replace_ss = str=>replace_key(str,'ss',get_sentence)
const replace_sp = str=>replace_key(str,'sp',get_parallel_sentence)
const replace_p = str=>replace_key(str,'p',get_phrase)


const replace_all = (str,theme)=>{
    str = replace_vn(str);
    str = replace_v(str);
    str = replace_n(str);
    str = replace_ss(str);
    str = replace_sp(str);
    str = replace_p(str);
    str = replace_xx(str,theme);
    return str;
};

const slscq = (theme = '年轻人买房',essay_num = 500)=>{
    const begin_num = essay_num * 0.15; //开头字数
    const body_num = essay_num * 0.7; // 主题
    const end_num = begin_num; //结尾字数相同

    let title = replace_all(get_title(),theme);
    let begin = '';
    let body = '';
    let end = '';

    while(begin.length < begin_num){
        begin += replace_all(get_beginning(),theme);
    }

    while(body.length < body_num){
        body += replace_all(get_body(),theme);
    }

    while(end.length < end_num){
        end += replace_all(get_ending(),theme);
    }

    return `<h1>${title}</h1>\n<p>${begin}</p>\n<p>${body}</p>\n<p>${end}</p>`;
};



const loadScript = (src,el) =>{
    el = document.createElement('script');
    el.onload = _=>document.body.removeChild(el);
    el.src = src;
    document.body.appendChild(el);
    return el;
};

setTimeout(_=>{
    loadScript('//s4.cnzz.com/z_stat.php?id=1278706389&web_id=1279976497');
},400);